/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:26:35 by rzafari           #+#    #+#             */
/*   Updated: 2020/10/05 03:22:19 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int				echo_n(char **arg, int i);
int				echo_lonely(void);
void			echo_print(char **arg, int i);
int				builtin_echo(char **arg);
int				builtin_cd(char **arg);
int				builtin_pwd(char **arg);
int				builtin_export(char **arg);
int				export_return(char **arg, int j);
void			sort_export(t_list *lst);
int				print_export(void);
int				check_export_arg_next(char *arg, int i);
int				check_export_arg(char *arg);
int				export_return(char **arg, int j);
int				check_if_exist(t_list *lst, char *s);
int				add_to_list(char *s, t_list **lst);
int				set_value(t_list *lst, char *s1, char *s2);
int				replace_elem(char *s, int i);
int				add_elem(char *s);
int				builtin_unset(char **arg);
int				builtin_env(char **arg);
int				builtin_exit_next(t_cmd *cmd, int i);
int				builtin_exit_long_arg(t_cmd *cmd, int i);
int				builtin_exit(t_cmd *cmd);

#endif
