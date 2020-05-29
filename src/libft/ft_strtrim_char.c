/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:22:56 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:31:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char			*ft_strtrim_char(char *s1, char const set)
{
	int		i;
    int     j;
	char	*str;

    i = -1;
    j = ft_strlen(s1);
    while(s1[++i] != '\0')
    {
        if (s1[i] == set)
            j--;
    }
    if (!(str = (char*)malloc(sizeof(char) * (j + 1))))
        return(NULL);
    i = 0;
    j = 0;
    while (s1[i] != '\0')
    {
        if (s1[i] != set)
        {
            str[j++] = s1[i];
        }
        i++;
    }
    str[i] = '\0';
    return (str);
}