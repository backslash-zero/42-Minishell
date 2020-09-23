/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 11:21:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/23 13:19:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
			ft_printf_fd(2, "tab[%d][%d] = %s\n",i, j,tab[i][j]);
			printf("tab[%d][%d] = %s\n",i, j,tab[i][j]);
		//	free(tab[i][j]);
			j++;
		}
		//free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tool(char **cmd_arg, char **arg, int free_env)
{
	if (cmd_arg)
		free(cmd_arg);
	if (arg)
		free(arg);
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
