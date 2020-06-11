/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 00:07:18 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/11 00:07:18 by cmeunier         ###   ########.fr       */
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
