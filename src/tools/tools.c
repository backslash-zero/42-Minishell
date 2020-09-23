/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:06:25 by celestin          #+#    #+#             */
/*   Updated: 2020/09/15 15:18:12 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		print_gret(char *str)
{
	printf("%s		--	g_ret = %d\n", str, g_ret);
}

void		printtab(char **tab)
{
	int i;

	i = 0;
	printf("len tab: %d\n", arg_len(tab));
	while (tab[i])
	{
		printf("str-%d: %s\n", i, tab[i]);
		i++;
	}
}

int		arg_3_len(char ***arg)
{
	int i;

	i = 0;
	if (arg)
		while (arg[i])
			i++;
	return (i);
}

void		print3Dtab(char ***tab)
{
	int i;
	i = 0;
	
	printf("len ***tab: %d\n", arg_3_len(tab));
	while (tab[i])
	{
		printf("**tab: %d\n", i);
		printtab(tab[i]);
		i++;
	}
}