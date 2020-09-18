/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:41:16 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/18 08:24:17 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		builtin_pwd(char **arg)
{
	char *dir;

	dir = NULL;
	(void)arg;
	if (arg_len(arg) > 1)
		return (ft_error(PWD_MANY_ARG, NULL, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	ft_putstr_fd(1, dir);
	ft_putchar_fd(1, '\n');
	free(dir);
	return (0);
}
