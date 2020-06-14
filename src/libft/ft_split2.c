#include "../../incs/libft.h"

static	char			*ft_strcrea(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != c)
    	i++;
    if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
    while (s[j] != '\0' && s[j] != c)
    {
        str[j] = s[j];
        j++;
    }
    str[j] = '\0';
    return (str);
}

static	int				ft_calcnbwords(char const *s, char c)
{
	int tot;
	int i;

	tot = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
            i++;
        if (s[i] != c && s[i] != '\0')
		{
			tot++;
			while (s[i] != c && s[i] != '\0')
            	i++;
        }
	}
	return (tot);
}

static	char			**freefunc(char **s)
{
	while (s)
	{
		free(s);
		s++;
	}
	return (NULL);
}

char    *addspace(char const *s, char c, char c2)
{
    int i;
    int j;
    int tot;
    char    *str;

    i = 0;
    tot = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c2)
        {
            if (i != 0 && s[i - 1] == c)
                tot++;
            if (i < (signed int)ft_strlen(s) && s[i + 1] == c)
                tot++;
            else
                tot += 2;        
        }
        tot++;
        i++;
    }
    i = 0;
    j = 0;
    if (!(str = (char *)malloc(sizeof(char) * (tot + 1))))
        return (NULL);
    while (s[j] != '\0' && i < tot)
    {
        if (s[j] == c2)
        {
            if (s[j - 1] != c)
            {
                str[i] = c;
                i++;
            }
            str[i] = s[j];
            if (s[j + 1] != c)
            {
                i++;
                str[i] = c;
            }
        }
        else
            str[i] = s[j];
        j++;
        i++;
    }
    str[i] = '\0';
    i = 0;
    while (str[i])
        i++;
    return (str);
}

char					**ft_split2(char const *s, char c, char c2)
{
	unsigned int	i;
	unsigned int	j;
    char            *s2;
	char			**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
    s2 = addspace(s, c, c2);
	if (!(res = (char **)malloc(sizeof(char *) * (ft_calcnbwords(s2, c) + 1))))
		return (NULL);
	while (s2[i] != '\0')
	{
		while (s2[i] != '\0' && s2[i] == c)
			i++;
        if (s2[i] != '\0' && s2[i] != c)
		{
			if (!(res[j] = ft_strcrea(s2 + i, c)))
				return (freefunc(res));
			j++;
		}
		while (s2[i] != '\0' && s2[i] != c)
        	i++;
    }
	res[j] = NULL;
    free (s2);
	return (res);
}