#ifndef BUILTIN_H
# define BUILTIN_H

int     builtin_echo(int fd, char **arg);
int		builtin_cd(int fd, char **arg);
int		builtin_pwd(int fd, char **arg);
int		builtin_export(int fd, char **arg);
int		builtin_unset(int fd, char **arg);
int     builtin_env(int fd, char **arg);
int		builtin_exit(int fd, char **arg);

#endif