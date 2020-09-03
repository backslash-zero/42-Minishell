/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:05:54 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/03 14:29:58 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <memory.h>

int		    ft_count_pipe(char **arg);
void        ft_pipe(void);
void        ft_pipe_2(char **arg_list);
int		    loop_pipe(char ***cmd);
char		**last_cmd_arg(char **arg);
char		**cmd_arg_get(char **arg, int *i);
char		***prepare_cmd(char **arg_list, int pipe_len);

#endif