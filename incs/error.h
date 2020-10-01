/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:29:12 by rzafari           #+#    #+#             */
/*   Updated: 2020/10/01 19:17:44 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define CMD_NOT_FOUND	"Minishell: %s: command not found\n"
# define MANY_ARGS		"Minishell: %s: too many arguments\n"
# define NO_ARG			"Minishell: %s: not enough arguments\n"
# define NO_FILE		"Minishell: %s: No such file or directory\n"
# define NO_FILE_LS		"ls: : No such file or directory\n"
# define EXIT_NUM		"Minishell: exit: %s: numeric argument required\n"
# define INVALID_ID_X	"Minishell: export: '%s': not a valid identifier\n"
# define INVALID_OPT_ID_X	"Minishell: export: %s: invalid option\n"
# define INVALID_ID_U	"Minishell: unset: '%s': not a valid identifier\n"
# define INVALID_OPT_ID_U	"Minishell: unset: %s: invalid option\n"
# define SYNTAX_ERR		"Minishell: syntax error near unexpected token\n"
# define RNO_FILE		"Minishell: %s: No such file or is a directory\n"
# define RNO_CREA		"Minishell: %s: File could not be created\n"
# define PWD_MANY_ARGS  "pwd: too many arguments\n"
# define NO_RIGHTS      "Minishell: %s: Permission denied\n"
# define AMBIGUOUS      "Minishell: %s: ambiguous redirect\n"

int		ft_error(char *msg, char *tofree, char **tab, char *param);
int		ft_strerror(void *tofree, char **tab, char *param, char *param2);

#endif
