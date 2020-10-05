/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:05:54 by rzafari           #+#    #+#             */
/*   Updated: 2020/10/05 13:28:58 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <memory.h>

typedef struct	s_pipe_cmd{
	int			len;
	char		***cmd;
	int			pfd[2];
	pid_t		proc;
	int			fd_in;
	int			i;
	char		*s;
	int			ret_red;
	char		**tab_env;
	int			check_redir;
	t_parse		parse;
}				t_pipe_cmd;

int				ft_count_pipe(char **arg);
void			ft_pipe(void);
int				check_redir(char **s);
void			count_redir_pipe(char **s, t_cmd *cmd);
void			redir_pipe(char **s, t_pipe_cmd *pipe_cmd, t_cmd *cmd);
int				loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd);
int				init_t_pipe(t_pipe_cmd *pipe_cmd, char **arg_list);
int				ft_pipe_2(char **arg_list, t_cmd *cmd);
char			**cmd_arg_get(char **arg, int *i);
char			**last_cmd_arg(char **arg);
char			***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd);
void			pipe_wait(int status, t_pipe_cmd *pipe_cmd);
int				pipe_default(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int *ret_exec);
void			toggle_redir(char **s, int i, t_pipe_cmd *pipe_cmd);
int				pipe_fork(t_pipe_cmd *pipe_cmd);
void			pipe_dups(t_pipe_cmd *pipe_cmd);
void			free_and_exit(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int exit_code);
int				pipe_arg_cleanup(t_pipe_cmd *pipe_cmd);

#endif
