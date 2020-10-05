/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:52:27 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 13:26:54 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		pipe_arg_cleanup(t_pipe_cmd *pipe_cmd)
{
	int		i;
	t_cmd	new_cmd;
	char	**tmp;

	tmp = pipe_cmd->cmd[pipe_cmd->i];
	i = 0;
	if (!(new_cmd.arg = malloc(sizeof(char *) * (arg_len(pipe_cmd->cmd[pipe_cmd->i]) + 1))))
		return (ft_strerror(NULL, pipe_cmd->cmd[pipe_cmd->i], NULL, NULL));
	while (pipe_cmd->cmd[pipe_cmd->i][i])
	{
		new_cmd.arg[i] = ft_strdup(pipe_cmd->cmd[pipe_cmd->i][i]);
		i++;
	}
	new_cmd.arg[i] = NULL;
	if (!arg_cleanup(&new_cmd))
		return (ft_strerror(NULL, pipe_cmd->cmd[pipe_cmd->i], NULL, NULL));
	pipe_cmd->cmd[pipe_cmd->i] = new_cmd.arg;
	free_tab(tmp);
	return (1);
}

void	free_and_exit(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int exit_code)
{
	free_tab_3d(pipe_cmd->cmd);
	free_tool(cmd->arg, cmd->input_arg, 1);
	free_tab(pipe_cmd->tab_env);
	exit(exit_code);
}

int		ft_count_pipe(char **arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
			count++;
		i++;
	}
	return (count);
}

int		check_redir(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0 || ft_strcmp(s[i], ">>") == 0 ||
		ft_strcmp(s[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	count_redir_pipe(char **s, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->nb_redir = 0;
	cmd->apply_redir = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0 || ft_strcmp(s[i], ">>") == 0 ||
		ft_strcmp(s[i], "<") == 0)
			cmd->nb_redir++;
		i++;
	}
}

char	**copy_arg_pipe(char **arg, char **cmd_arg, int cmd_arg_len)
{
	int l;
	int j;

	l = 0;
	j = 0;
	if (!ft_strcmp(arg[0], "<") || !ft_strcmp(arg[0], ">"))
	{
		cmd_arg[j] = ft_strdup("echo");
		cmd_arg[++j] = ft_strdup("-n");
		j++;
	}
	while (j < cmd_arg_len)
	{
		cmd_arg[j] = ft_strdup(arg[l]);
		j++;
		l++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}
