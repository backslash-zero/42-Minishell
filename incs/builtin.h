#ifndef BUILTIN_H
# define BUILTIN_H


char	*current_dir(void);
int     builtin_env(void);
int 	builtin_pwd(void);
int 	builtin_cd(char **arg);

#endif