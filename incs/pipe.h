/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:05:54 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/03 16:53:59 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <memory.h>

typedef struct  s_pipe_cmd{
    int     len;
    char    ***cmd;
    int     pfd[2];
    pid_t	proc;
	int		fd_in;
	int		i;
	char 	*s;
	int 	ret_red;
    char    **tab_env;
}               t_pipe_cmd;

int		    ft_count_pipe(char **arg);
void        ft_pipe(void);
char		**last_cmd_arg(char **arg);
char		**cmd_arg_get(char **arg, int *i);
char		***prepare_cmd(char **arg_list, int pipe_len);

#endif