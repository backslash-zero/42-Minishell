#ifndef ERROR_H
# define ERROR_H

# define CMD_NOT_FOUND	"minishell: %s: command not found\n"
# define MANY_ARGS		"minishell: %s: too many arguments\n"
# define NO_ARG			"minishell: %s: not enough arguments\n"
# define NO_FILE		"minishell: %s: No such file or directory\n"
# define NO_FILE_LS		"ls: : No such file or directory\n"
# define EXIT_NUM		"minishell: exit: %s: numeric argument required\n"
# define INVALID_ID_X	"minishell: export: %s: not a valid identifier\n"
# define INVALID_ID_U	"minishell: unset: %s: not a valid identifier\n"
# define SYNTAX_ERR		"minishell: syntax error near unexpected token\n"
# define RNO_FILE		"minishell: %s: No such file or is a directory\n"
# define RNO_CREA		"minishell: %s: File could not be created\n"

int        ft_error(char *msg, char *param);
int        ft_strerror(void);

#endif