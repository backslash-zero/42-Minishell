/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:02:30 by cmeunier          #+#    #+#             */
/*   Updated: 2019/10/21 14:51:52 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*begin;

	if (!(begin = malloc(sizeof(t_list))))
		return (NULL);
	begin->content = content;
	begin->next = NULL;
	return (begin);
}
