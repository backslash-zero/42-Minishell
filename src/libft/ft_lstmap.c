/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:58:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:21:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*dl)(void *))
{
	t_list *new;
	t_list *element;

	if (!l || !(*f) || !dl)
		return (NULL);
	if (!(new = ft_lstnew((*f)(l->content))))
		return (NULL);
	l = l->next;
	while (l)
	{
		if (!(element = ft_lstnew((*f)(l->content))))
		{
			ft_lstclear(&new, dl);
			return (NULL);
		}
		ft_lstadd_back(&new, element);
		l = l->next;
	}
	return (new);
}
