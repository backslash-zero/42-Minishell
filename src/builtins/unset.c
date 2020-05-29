#include "../../incs/minishell.h"

int find_elem(char *s1, char *s2)
{
    int i;
    char *s3;

    i = 0;
    while (s1[i] != '=' && s1[i] != '\0')
        i++;
    if (!(s3 = ft_substr(s1, 0, i)))
        return (0);
    if (ft_strcmp(s3, s2) == 0)
    {
        free (s3);
        return (1);
    }
    free (s3);
    return (0);
}

t_list  *unset_env(t_list *lst, char *s)
{
    t_list  *lst2;
    t_list  *lst3;

    lst2 = lst;
   /* if (find_elem(lst2->content, s))
    {
        lst = lst->next;
        ft_lstdelone(lst2, free);
        return(lst);
    }
    else
    {
        lst3 = lst2->next;
        while (lst3)
        {
            if (find_elem(lst3->content, s))
            {
                lst2->next = lst3->next;
                ft_lstdelone(lst3, free);
                return(lst);
            }
            lst2 = lst3;
            lst3 = lst3->next;
        }
        return (lst);
    }*/
    while (lst2)
    {
        if (find_elem(lst2->content, s))
        {
            lst3 = lst2;
            lst2 = lst2->next;
            ft_lstdelone(lst3, free);
            return (lst);
        }
        lst2 = lst2->next;
    }
}

int		builtin_unset(char **s)
{
    int     i;
    t_list  *tmp0;
    t_list  *tmp1;

    i = 1;
    tmp0 = g_env;
    tmp1 = g_export;
    printf("i'm in unset\n");
    while (s[i] != '\0')
    {
        tmp0 = unset_env(tmp0, s[i]);
        tmp1 = unset_env(tmp1, s[i]);
        i++;
    }
	return(0);
}