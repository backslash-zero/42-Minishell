/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_nametab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:59:32 by rzafari           #+#    #+#             */
/*   Updated: 2020/08/31 18:26:27 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_builtinstab(t_parse *parse)
{
	parse->builtnb[0] = "echo";
	parse->builtnb[1] = "cd";
	parse->builtnb[2] = "pwd";
	parse->builtnb[3] = "export";
	parse->builtnb[4] = "unset";
	parse->builtnb[5] = "env";
	parse->builtnb[6] = "exit";
}

t_builtfunc_addr	builtins_func[] = {
	&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export,
	&builtin_unset, &builtin_env, &builtin_exit
};

int		ft_checkbuiltins(char **s, t_parse *parse)
{
	int i;
	int	good;

	i = 0;
	good = 0;
	while (i < NB_BUILINS && good != 1)
	{
		if (ft_strcmp(s[0], parse->builtnb[i]) == 0)
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
