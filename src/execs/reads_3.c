/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 23:04:58 by celestin          #+#    #+#             */
/*   Updated: 2020/09/25 02:01:44 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**tablst(t_list *lst)
{
	char	**ret;
	t_list	*tmp;
	int		i;

	ret = NULL;
	tmp = NULL;
	if (!(ret = malloc((ft_lstsize(lst) + 1) * sizeof(*ret))))
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (!(ret[i] = ft_strdup(tmp->content)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	get_len_semic(char **arg, int *i, int *len_new_arg_list)
{
	*len_new_arg_list = 0;
	while (*i < arg_len(arg) && ft_strcmp(arg[*i], ";") != 0)
	{
		*len_new_arg_list += 1;
		*i += 1;
	}
}

int		init_semic(t_cmd *cmd, char **arg, int *i)
{
	int		len_new_arg_list;

	len_new_arg_list = 0;
	while (*i < arg_len(arg) && ft_strcmp(arg[*i], ";") != 0)
	{
		len_new_arg_list++;
		*i += 1;
	}
	if ((cmd->arg = semicolon(arg, *i, len_new_arg_list)) == NULL)
	{
		free_tab(cmd->arg);
		return (-1);
	}
	return (1);
}

void	launch_start(t_cmd *cmd, char **arg)
{
	int		ret_exec;

	ret_exec = 0;
	if (ft_count_pipe(cmd->arg) > 0)
	{
		ret_exec = ft_pipe_2(cmd->arg, cmd);
		if (ret_exec == -1)
			g_ret = 127;
	}
	else
		ret_exec = launch_exec(arg, cmd);
	printf("ret_exec launch start = %d g_ret = %d\n", ret_exec, g_ret);
	if (ret_exec == -2 || g_ret == 127)
	{
		//free_tab(arg);
		printf("qzdsqzs\n");
		free_tool(cmd->arg, cmd->input_arg, 1);
		exit(127);
	}
	free_tmp_tab(cmd->arg);
}

int		launch(char *input, t_cmd *cmd)
{
	char	**arg;
	int		i;

	if (!(arg = parsing(input)))
		return (0);
	cmd->input_arg = arg;
	i = 0;
	while (arg[i] != NULL)
	{
		if (init_semic(cmd, arg, &i) == -1)
			return (ft_strerror(NULL, arg, NULL, NULL));
		launch_start(cmd, arg);
		if (arg[i] == NULL)
			break ;
		i++;
	}
	free_tab(arg);
	return (0);
}
