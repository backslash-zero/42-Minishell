/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:05:54 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/07 13:51:36 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

#include <memory.h>

int		    ft_count_pipe(char **arg);
void        ft_pipe(void);
//char		**last_cmd_arg(char **arg, t_pipe_cmd *pipe_cmd);
//char		**cmd_arg_get(char **arg, int *i, t_pipe_cmd *pipe_cmd);
//char		***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd);

#endif