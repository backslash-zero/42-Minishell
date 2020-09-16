/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:30:06 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 17:54:17 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct	s_newstr
{
	char	*str;
	int		len;
	int		open;
	int		expand;
	char	quote;
}				t_newstr;

typedef struct	s_parsing_tool
{
	int		size;
	char	*input;
	char	**arg;
	int		open;
	char	quote;
	int		empty_var;
}				t_parsing_tool;

char			**parsing(char *input);
int				ft_split_args(t_parsing_tool *tool);
int				size_arg_tool(t_parsing_tool *tool);
void			switcher_quote(t_parsing_tool *tool, char c);
char			*ft_addsubstr(int i, int j, t_parsing_tool *tool);
void			switcher_quote(t_parsing_tool *tool, char c);
int				test_empty_quote(char c, char d);
int				cleanup_quotes(char **arg_list);
char			*clean_substring(char *str);
void			init_tool(t_parsing_tool *tool);
int				append_string_to_arg(int *i, int *j, int *n,
				t_parsing_tool *tool);
int				append_semicolon(int *i, int *j, int *n, t_parsing_tool *tool);
int				is_quote(char c);
int				is_space(char c);
int				is_semic(char c);
int				is_dollar(char c);
int				is_equal(char c);
int				test_lone_dollar(char *str, int i);
int				expand_env(t_parsing_tool *tool);
int				replace_var(t_parsing_tool *tool, int i, char *var,
				char *env_name);
int				remove_var(t_parsing_tool *tool, int i, char *env_name);
int				insert_env_var(t_parsing_tool *tool, int i);
char			*get_var_name(t_parsing_tool *tool, int i);
char			*parsing_variable(t_parsing_tool *tool, char *str);
int				calc_len_newstr(char *var, char *input, char *env_name, int i);
void			quote_checker(t_parsing_tool *tool, int i, int *n);
int				semic_checker(t_parsing_tool *tool, int i, int *n);
int				envvar_authorized_character(char c, int first_char);
void			skipspaces(t_parsing_tool *tool, int *i, int *j);
int				checkifquotes(char *str);
int				removequotes(char **arg_list, int i);
int				redir_r_checker(t_parsing_tool *tool, int *i, int *n);
int				redir_l_checker(t_parsing_tool *tool, int i, int *n);
int				pipe_checker(t_parsing_tool *tool, int i, int *n);
int				redir_pipe_checker(t_parsing_tool *tool, int *i, int *n);
int				append_redir_pipe(int *i, int *j, int *n, t_parsing_tool *tool);
int				is_redir_or_pipe(char c);
int				is_pipe(char c);
int				is_redir_l(char c);
int				is_redir_r(char c);
int				is_backslash(char c);
int				check_backslash(char *str);
int				new_len_backslash(char *str);
int				ft_clean_backslash(char **arg_list, int a);
int				ft_backslash(char **arg_list);
int				replace_g_ret(char **arg_list, int i);
int				check_g_ret_var(char **arg_list);
int				is_g_ret_var(char *str);
int				insert_ret(t_parsing_tool *tool, int i);
int				parsing_checks(int *i, int *j, int *n, t_parsing_tool *tool);
int				check_var(char **arg_list);
int				includes_var(char *str);
int				check_char_quote(char *str, int i);
int				check_bf_bs(char *str, int i);

#endif
