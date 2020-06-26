/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:02:08 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/25 20:21:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *ptr;
	t_list *previous;

	if (!lst || !*lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		previous = ptr;
		ptr = ptr->next;
		ft_lstdelone(previous, del);
	}
	*lst = 0;
}
