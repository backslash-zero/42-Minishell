/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:26:35 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 13:17:04 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void		echo_print(char **arg, int i);
int			builtin_echo(char **arg);
int			builtin_cd(char **arg);
int			builtin_pwd(char **arg);
int			builtin_export(char **arg);
int			check_if_exist(t_list *lst, char *s);
int			add_to_list(char *s, t_list **lst);
int			set_value(t_list *lst, char *s1, char *s2);
int			replace_elem(char *s, int i);
int			add_elem(char *s);
int			builtin_unset(char **arg);
int			builtin_env(char **arg);
int			builtin_exit(char **arg);

#endif
