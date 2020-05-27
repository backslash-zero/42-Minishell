/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:47:40 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:31:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static	int		checkinset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*str;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (checkinset(s1[i], set))
		i++;
	if (!s1[i])
		return (ft_calloc(1, 1));
	start = i;
	i = ft_strlen(s1) - 1;
	while (checkinset(s1[i], set))
		i--;
	len = i - start + 1;
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
