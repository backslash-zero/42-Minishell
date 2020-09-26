/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:35:56 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/25 16:51:38 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT_SIZE 131072
# define NB_BUILINS 6
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
# include "ft_printf.h"
# include "parsing.h"
# include "builtin.h"
# include "pipe.h"

typedef int		t_ret;
t_ret			g_ret;
typedef int		t_prompt;
t_prompt		g_print;
typedef int		t_signal;
t_signal		g_signal;

typedef int		(*t_builtfunc_addr)(char **s);

void			ft_builtinstab(t_cmd *cmd);
int				ft_checkbuiltins(char **s, t_cmd *cmd);
void			print_prompt_prefix(void);
void			prompt(void);
int				init_semic(t_cmd *cmd, char **arg, int *i);
int				ft_exec_father(char **tab_env, char **arg_list);
int				ft_exec_child(char **tab_env, char **arg_list);
int				launch_ft_exec(t_cmd *cmd);
char			*check_paths(char **tab_env, char **arg_list);
int				dup_return(int value);
int				launch_exec(char **arg, t_cmd *cmd);
void			launch_start(t_cmd *cmd, char **arg);
int				launch(char *input, t_cmd *cmd);
void			free_tool(char **cmd_arg, char **arg, int free_env);
void			free_tab(char **tab);
void			free_tab_3d(char ***tab);
void			free_tmp_tab(char **tofree);
void			assign_and_free(char **newstr, char **oldstr);
void			ft_strncpy(char *dest, char *src, int len);
int				arg_len(char **arg);
int				ft_exec(char **arg_list);
int				find_first_redir(t_cmd *cmd);
int				find_first_redir(t_cmd *cmd);
int				arg_is_redir(char *str);
int				sort_cmd(t_cmd *cmd, t_sort_redir *sort);
int				sort_redir(t_cmd *cmd);
int				redirection(t_cmd *cmd);
void			redir_exec(char **arg_list, t_cmd *cmd, int fd);
int				apply_redirections(char **arg, t_cmd *cmd, int fd);
int				r_anglebracket(char **arg, t_cmd *cmd, char *name);
int				r_dbanglebracket(char **arg, t_cmd *cmd, char *name);
int				l_anglebracket(char **arg, t_cmd *cmd, char *name);
char			**deletebracket(char **arg);
char			**semicolon(char **arg, int i, int len_new_arg_list);
char			*find_path_env(char **env, char *arg);
int				try_path(char *s);
char			*catch_path(char *test, char *arg);
void			insert_copy_rest(t_parsing_tool *tool, char *newstr,
				int i, int j);
char			*find_correct_path(char *s, char *arg);
char			*try_absolut_path(char *arg);
char			**tablst(t_list *lst);
void			fd_dup(int i);
int				ft_pipe_2(char **arg_list, t_cmd *cmd);
int				loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd);
char			**last_cmd_arg(char **arg);
char			**cmd_arg_get(char **arg, int *i);
char			***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd);
void			check_signal(int status);
void			get_len_semic(char **arg, int *i, int *len_new_arg_list);

#endif
