/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 11:21:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/10/05 00:54:10 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	assign_and_free_3(char ***newtab, char ***oldtab)
{
	char	**tmp;

	tmp = *oldtab;
	*oldtab = *newtab;
	free_tab(tmp);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_3d(char ***tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tool(char **cmd_arg, char **arg, int free_env)
{
	if (cmd_arg)
		free_tab(cmd_arg);
	if (arg)
		free_tab(arg);
	if (free_env)
	{
		ft_lstclear(&g_env, free);
		ft_lstclear(&g_export, free);
	}
}

void	free_tmp_tab(char **tofree)
{
	char	**tmp;

	tmp = tofree;
	free_tab(tmp);
}

void	assign_and_free(char **newstr, char **oldstr)
{
	char	*tmp;

	tmp = *oldstr;
	*oldstr = *newstr;
	free(tmp);
}
