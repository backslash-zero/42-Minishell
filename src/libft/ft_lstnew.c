/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:02:30 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:21:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*begin;

	if (!(begin = malloc(sizeof(t_list))))
		return (NULL);
	begin->content = content;
	begin->next = NULL;
	return (begin);
}
