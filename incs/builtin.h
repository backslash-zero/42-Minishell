  
#ifndef BUILTIN_H
# define BUILTIN_H


char	*current_dir(void);
int     builtin_echo(char **arg);
int		builtin_cd(char **arg);
int		builtin_pwd(char **arg);
int		builtin_export(char **arg);
int		builtin_unset(char **arg);
int     builtin_env(char **arg);
int		builtin_exit(char **arg);

#endif