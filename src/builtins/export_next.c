/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:10:10 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 12:06:58 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		add_to_list(char *s, t_list **lst)
{
	t_list *lst1;

	if (!(lst1 = malloc(sizeof(t_list))))
		return (0);
	if (!(lst1->content = ft_strdup(s)))
		return (0);
	lst1->next = NULL;
	ft_lstadd_back(lst, lst1);
	return (1);
}

int		set_value(t_list *lst, char *s1, char *s2)
{
	char	*tmp;
	char	*value;
	char	*s3;
	int		i;

	if (!(value = ft_strdup(s1)))
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] != '=' && lst->content[i])
			i++;
		s3 = ft_substr(lst->content, 0, i);
		if (ft_strcmp(s3, s2) == 0)
		{
			tmp = lst->content;
			lst->content = value;
			free(tmp);
			return (1);
		}
		lst = lst->next;
		free(s3);
	}
	return (0);
}

char	*catch_name(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	if (i > 0)
		return (ft_substr(s, 0, i));
	else
		return (NULL);
}

int		check_if_exist(t_list *lst, char *s)
{
	t_list	*lst2;
	char	*name;
	char	*tmp;
	int		i;

	if ((name = catch_name(s)) == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		lst2 = lst->next;
		while (lst->content[i] != '=' && lst->content[i])
			i++;
		tmp = ft_substr(lst->content, 0, i);
		if (ft_strcmp(name, tmp) == 0)
		{
			free(name);
			free(tmp);
			return (i);
		}
		free(tmp);
		lst = lst2;
	}
	free(name);
	return (0);
}
