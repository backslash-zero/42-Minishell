/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:51:51 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:31:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static int		sze(char const *s, char c)
{
	int		count;
	int		n;

	n = 1;
	count = 0;
	while (*s)
	{
		if (*s != c && n != 0)
		{
			count++;
			n = 0;
		}
		if (*s == c)
			n++;
		s++;
	}
	return (count);
}

static	void	*freebuffs(char **buff)
{
	char **tmp;

	tmp = buff;
	while (*tmp)
		free(tmp++);
	free(buff);
	return (0);
}

static	char	*c_addsubstr(char const *s_copy, char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = malloc(sizeof(char) * (ptr - s_copy + 1))))
		return (NULL);
	while (s_copy < ptr)
	{
		str[i] = *s_copy;
		i++;
		s_copy++;
	}
	str[i] = '\0';
	return (str);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		n;
	char	*ptr;
	char	*s_copy;

	n = 0;
	if (!s || !(result = malloc(sizeof(char *) * (sze((char *)s, c) + 1))))
		return (NULL);
	s_copy = (char *)s;
	result[sze(s_copy, c)] = NULL;
	ptr = (char *)s_copy;
	while (*s_copy && n <= sze(s, c))
	{
		while (*ptr != c && *ptr != '\0')
			ptr++;
		if (ptr - s_copy > 0)
		{
			if (!(result[n++] = c_addsubstr(s_copy, ptr)))
				return (freebuffs(result));
			s_copy = ptr;
		}
		if (*ptr++ != '\0')
			s_copy++;
	}
	return (result);
}
