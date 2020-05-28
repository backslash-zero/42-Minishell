#include "minishell.h"

int     update_pwd(void)
{
    char *dir;
    char *old_dir;

    old_dir = NULL;
    if (!(old_dir = get_var(g_env, "PWD=")))
		// error
	if (!(dir = getcwd(dir, 0)))
		// error
    set_var(g_env, "PWD=", dir);
	set_var(g_export, "PWD=", dir);
	set_var(g_env, "OLDPWD=", old_dir);
	set_var(g_export, "OLDPWD=", old_dir);
    free(dir);
    free(old_dir);
}

int 	builtin_cd(char **arg)
{
	char *c_dir;
	char *new_dir;
	
	c_dir = current_dir();
	if (arg_len(arg) == 1)
	{
		if (!(new_dir = get_var(g_env, "HOME=")))
            //error
	}
    else
    {
        if (!ft_strcmp(args[1], ""))
			return (0);
        new_dir = arg[1]
    }
	if (chdir(new_dir) == -1);
        //error
    update_pwd();
}

