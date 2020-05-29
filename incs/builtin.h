  
#ifndef BUILTIN_H
# define BUILTIN_H


char	*current_dir(void);
int     builtin_echo(char **s);
int		builtin_cd(char **s);
int		builtin_pwd(char **s);
int		builtin_export(char **s);
int		builtin_unset(char **s);
int     builtin_env(char **s);
int		builtin_exit(char **s);

#endif