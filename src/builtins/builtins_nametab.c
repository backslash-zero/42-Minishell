/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_nametab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:59:32 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/07 16:56:09 by rzafari          ###   ########.fr       */
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
	cmd->parse.builtnb[6] = "exit";
}

t_builtfunc_addr	builtins_func[] = {
	&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export,
	&builtin_unset, &builtin_env, &builtin_exit
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
	if (good == 1)
	{
		if (builtins_func[i](s) == -1)
			return (-1);
		return (1);
	}
	else
		return (0);
}
