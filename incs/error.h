/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:29:12 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 12:11:40 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define CMD_NOT_FOUND	"MiniShell: %s: command not found\n"
# define MANY_ARGS		"MiniShell: %s: too many arguments\n"
# define NO_ARG			"MiniShell: %s: not enough arguments\n"
# define NO_FILE		"MiniShell: %s: No such file or directory\n"
# define NO_FILE_LS		"ls: : No such file or directory\n"
# define EXIT_NUM		"MiniShell: exit: %s: numeric argument required\n"
# define INVALID_ID_X	"MiniShell: export: '%s': not a valid identifier\n"
# define INVALID_OPT_ID_X	"MiniShell: export: %s: invalid option\n"
# define INVALID_ID_U	"MiniShell: unset: '%s': not a valid identifier\n"
# define INVALID_OPT_ID_U	"MiniShell: unset: %s: invalid option\n"
# define SYNTAX_ERR		"MiniShell: syntax error near unexpected token\n"
# define RNO_FILE		"MiniShell: %s: No such file or is a directory\n"
# define RNO_CREA		"MiniShell: %s: File could not be created\n"
# define PWD_MANY_ARGS  "pwd: too many arguments\n"
# define NO_RIGHTS      "MiniShell: %s: Permission denied\n"

int		ft_error(char *msg, char *tofree, char **tab, char *param);
int		ft_strerror(void *tofree, char **tab, char *param, char *param2);

#endif
