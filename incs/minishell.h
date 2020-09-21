/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:35:56 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 14:57:06 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT_SIZE 131072
# define NB_BUILINS 7
# define TRUE  1
# define FALSE 0

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "error.h"
# include "libft.h"
# include "env.h"
# include "builtin.h"
# include "ft_printf.h"
# include "parsing.h"
# include "pipe.h"
# include "tools.h"

typedef int		t_ret;
t_ret			g_ret;
typedef int		t_prompt;
t_prompt		g_print;
typedef int		t_signal;
t_signal		g_signal;

typedef int		(*t_builtfunc_addr)(char **s);

typedef struct	s_parse
{
	char	*builtnb[NB_BUILINS];
}				t_parse;

typedef struct	s_pipe_cmd{
	int		len;
	char	***cmd;
	int		pfd[2];
	pid_t	proc;
	int		fd_in;
	int		i;
	char	*s;
	int		ret_red;
	char	**tab_env;
	int		check_redir;
	t_parse	parse;
}				t_pipe_cmd;

typedef struct	s_cmd{
	char	**arg;
	int		nb_redir;
	int		apply_redir;
	int		redir_ok;
	t_parse	parse;
}				t_cmd;

void			ft_builtinstab(t_cmd *cmd);
int				ft_checkbuiltins(char **s, t_cmd *cmd);
void			print_prompt_prefix(void);
void			prompt(void);
int				launch(char *input, t_cmd *cmd);
void			free_tab(char **tab);
void			free_tab_3d(char ***tab);
void			assign_and_free(char **newstr, char **oldstr);
void			ft_strncpy(char *dest, char *src, int len);
int				arg_len(char **arg);
int				ft_exec(char **arg_list);
int				redirection(t_cmd *cmd);
int				r_anglebracket(char **arg, t_cmd *cmd, char *name);
int				r_dbanglebracket(char **arg, t_cmd *cmd, char *name);
int				l_anglebracket(char **arg, t_cmd *cmd, char *name);
char			**deletebracket(char **arg);
char			**semicolon(char **arg, int i, int len_new_arg_list);
char			*find_path_env(char **env, char *arg);
char			*try_absolut_path(char *arg);
char			**tablst(t_list *lst);
void			fd_dup(int i);
int				ft_pipe_2(char **arg_list, t_cmd *cmd);
int				loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd);
char			**last_cmd_arg(char **arg, t_pipe_cmd *pipe_cmd);
char			**cmd_arg_get(char **arg, int *i, t_pipe_cmd *pipe_cmd);
char			***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd);
void			check_signal(int status);

void			printtab(char **tab);

#endif
