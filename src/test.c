#include "../incs/minishell.h"

// set_var(g_env, "PWD=", current_dir());

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char **arg;
	char **arg_just_cd;

    arg = malloc(sizeof(char*)*2);
    arg_just_cd = malloc(sizeof(char*)*1);
    g_env = init_env(&g_env, envp);
    builtin_env(arg);
    ft_putstr("\n\n");
    ft_putstr("\n\n");
    builtin_pwd(arg);
    ft_putstr("\n\n");
    arg[0] = "cd";
    arg[1] = "src";
    // printf("len arg:    %d\n", arg_len(arg));
    // printf("len arg 2:  %d\n", arg_len(arg_just_cd));
    builtin_cd(arg);
    builtin_pwd(arg);
    ft_putstr("\n\n");
    arg[0] = "cd";
    arg[1] = "..";
    builtin_cd(arg);
    builtin_pwd(arg);
    ft_putstr("\n\n");
    arg[0] = "cd";
    arg[1] = "/Users/celestin/Documents/";
    builtin_cd(arg);
    builtin_pwd(arg);
    ft_putstr("\n\n");
    arg_just_cd[0] = "cd";
    builtin_cd(arg_just_cd);
    builtin_pwd(arg);
	// free env
    ft_putstr("\n\n");
    ft_putstr("\n\n");
    ft_putstr("\n\n");
    ft_putstr("\n\nExport & unset test\n\n");
    arg[0] = "export";
    arg[1] = "minishell=2";
    builtin_export(arg);
    builtin_env(arg);

    ft_putstr("\n\n");
    /*arg[0] = "unset";
    arg[1] = "minishell";
    builtin_unset(arg);
    builtin_env(arg);*/
    
    ft_putstr("\n\n");
    arg[0] = "export";
    arg[1] = "testexport=5";
    builtin_export(arg);
    builtin_env(arg);
    ft_putstr("\n\n");
    arg[0] = "export";
    arg[1] = "test=5";
    builtin_export(arg);
    builtin_env(arg);
    ft_putstr("\n\narg = Export\n");
    arg[0] = "export";
    arg[1] = NULL;
    builtin_export(arg);

	return (0);
}
