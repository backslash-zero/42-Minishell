/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_nametab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:59:32 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/23 15:06:36 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_builtinstab(t_cmd *cmd)
{
	cmd->parse.builtnb[0] = "echo";
	cmd->parse.builtnb[1] = "cd";
	cmd->parse.builtnb[2] = "pwd";
	cmd->parse.builtnb[3] = "export";
	cmd->parse.builtnb[4] = "unset";
	cmd->parse.builtnb[5] = "env";
}

t_builtfunc_addr	g_builtins_func[] = {
	&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export,
	&builtin_unset, &builtin_env
};

int		ft_checkbuiltins(char **s, t_cmd *cmd)
{
	int i;
	int	good;

	i = 0;
	good = 0;
	while (i < NB_BUILINS && good != 1)
	{
		if (ft_strcmp(s[0], cmd->parse.builtnb[i]) == 0)
			good = 1;
		if (good != 1)
			i++;
	}
	if (good == 1 || !ft_strcmp(s[0], "exit"))
	{
		if (!ft_strcmp(s[0], "exit"))
			builtin_exit(cmd);
		else if (g_builtins_func[i](s) == -1)
			return (-1);
		return (1);
	}
	else
		return (0);
}
