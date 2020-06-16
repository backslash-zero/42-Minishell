/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:58:29 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/16 23:05:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int     update_pwd(void)
{
    char *dir;
    char *old_dir;

    dir = NULL;
    old_dir = NULL;
    if (!(old_dir = get_var(g_env, "PWD=")))
        return(ft_strerror(NULL, NULL, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
        return(ft_strerror(old_dir, NULL, NULL, NULL));
    set_var(g_env, "PWD=", dir);
	set_var(g_export, "PWD=", dir);
	set_var(g_env, "OLDPWD=", old_dir);
	set_var(g_export, "OLDPWD=", old_dir);
    free(dir);
    free(old_dir);
    return (0);
}

int 	builtin_cd(int fd, char **arg)
{
	char *new_dir;

	if (arg_len(arg) == 1)
	{
		if (!(new_dir = get_var(g_env, "HOME=")))
            return (ft_error("cd: HOME not set\n", NULL, NULL, NULL));
        if (chdir(new_dir) == -1)
            return (ft_strerror(new_dir, NULL, new_dir, NULL));
        free(new_dir);
	}
    else
    {
        if (!ft_strcmp(arg[1], ""))
			return (0);
        new_dir = arg[1];
        if (chdir(new_dir) == -1)
            return (ft_strerror(NULL, NULL, "cd", arg[1]));
    }
    return(update_pwd());
}
