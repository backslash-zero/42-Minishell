/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:30:06 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 23:54:51 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct	s_parsing_tool
{
	int			size;
	int			new_size;
	char		*input;
	char		*new_str;
	char		**arg;
	int			open;
	int			expand;
	char		quote;
	int			empty_var;
	int			pre_bs;
}				t_parsing_tool;

typedef struct	s_parse
{
	char		*builtnb[NB_BUILINS];
}				t_parse;

int				size_arg_tool(t_parsing_tool *tool);
int				conditions_split(t_parsing_tool *tool, int j);
int				ft_split_args(t_parsing_tool *tool);
char			**malloc_arg(t_parsing_tool *tool);
char			**parsing(char *input);

char			*ft_addsubstr(int i, int j, t_parsing_tool *tool);
int				append_str2arg(int *i, int *j, int *n, t_parsing_tool *tool);
int				append_semicolon(int *i, int *j, int *n, t_parsing_tool *tool);
int				append_redir_pipe(int *i, int *j, int *n, t_parsing_tool *tool);
int				parsing_checks(int *i, int *j, int *n, t_parsing_tool *tool);

int				arg_cleanup(char **arg);

int				insert_env_var(t_parsing_tool *tool, int i);
int				conditions_expand_env(t_parsing_tool *tool, int i);
int				expand_env(t_parsing_tool *tool);
int				check_var(char **arg_list);

int				replace_g_ret(char **arg_list, int i);
int				check_g_ret_var(char **arg_list);

void			ft_clean_and_cpy_switchers(t_parsing_tool *tool, int i);
void			ft_clean_and_cpy(t_parsing_tool *tool);
void			len_cleaned_str(t_parsing_tool *tool);
int				process_str(char **arg_list, int i);
int				ft_clean_bs_quote(char **arg_list);

int				is_redir_or_pipe(char c);
int				is_pipe(char c);
int				is_redir_l(char c);

int				is_redir_r(char c);
int				is_quote(char c);
int				is_backslash(char c);
int				is_bs_spec(char c);

int				is_space(char c);
int				is_equal(char c);
int				is_semic(char c);
int				test_lone_dollar(char *str, int i);
int				is_dollar(char c);

int				bs_count_conditions(int bs_count, t_parsing_tool *tool, int i);
int				backslash_loop_checker(t_parsing_tool *tool);

void			switcher_bs(t_parsing_tool *tool, int i);
void			cancel_pre_bs(t_parsing_tool *tool, int i);
void			bs_checker(t_parsing_tool *tool, int i);
int				check_backslash(t_parsing_tool *tool);
int				conditions_xtra_bs(t_parsing_tool *tool, int i);

int				insert_ret(t_parsing_tool *tool, int i);
int				is_g_ret_var(char *str);

int				check_char_quote(char *str, int i);
int				checkifquotes(char *str);
void			quote_checker(t_parsing_tool *tool, int i, int *n);
int				switcher_quote(t_parsing_tool *tool, int i);

int				redir_r_checker(t_parsing_tool *tool, int *i, int *n);
int				redir_l_checker(t_parsing_tool *tool, int i, int *n);
int				pipe_checker(t_parsing_tool *tool, int i, int *n);
int				redir_pipe_checker(t_parsing_tool *tool, int *i, int *n);

int				semic_checker(t_parsing_tool *tool, int i, int *n);

int				calc_len_newstr(char *var, char *input, char *env_name, int i);
int				rplc_vr(t_parsing_tool *tool, int i, char *var, char *env);
int				remove_var(t_parsing_tool *tool, int i, char *env_name);

char			*parsing_variable(t_parsing_tool *tool, char *str);
char			*get_var_name(t_parsing_tool *tool, int i);
int				includes_var(char *str);

void			init_tool(t_parsing_tool *tool);
void			skipspaces(t_parsing_tool *tool, int *i, int *j);
int				envvar_authorized_character(char c, int first_char);

#endif
