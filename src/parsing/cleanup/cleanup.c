/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:58:13 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 01:50:55 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

static void		printtab(char **arg)
{
	int i = 0;
	while (arg[i])
	{
		printf("str-%d	%s\n", i, arg[i]);
		i++;
	}
}

int		arg_cleanup(char **arg)
{
	int	ret;

	printf("new arg cleanup\n");
	if ((ret = check_var(arg)) < 1)
		return (ret);
	printtab(arg);
	if (!check_space_var(&arg))
		return (0);
	printf("after check space\n");
	printtab(arg);
	if (!check_g_ret_var(arg))
		return (0);
	printf("after g_ret\n");
	if (!ft_clean_bs_quote(arg))
		return (0);
	printf("end\n");
	return (1);
}
