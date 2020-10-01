/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:28:32 by celestin          #+#    #+#             */
/*   Updated: 2020/10/02 01:02:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		calc_len_newstr(char *var, char *input, char *env_name, int i)
{
	int	len_newstr;

	len_newstr = i;
	len_newstr += ft_strlen(var);
	len_newstr += (ft_strlen(input) - i - 1 - ft_strlen(env_name));
	return (len_newstr);
}

int		rplc_vr(t_parsing_tool *tool, int i, char *var, char *env)
{
	char	*newstr;
	int		j;
	int		k;

	k = i;
	j = 0;
	if (!(newstr = malloc(sizeof(char) *
		(calc_len_newstr(var, tool->input, env, i) + 1))))
		return (0);
	ft_strncpy(newstr, tool->input, i);
	ft_strncpy(&newstr[i], var, ft_strlen(var));
	i = i + ft_strlen(var);
	j = k + ft_strlen(env) + 1;
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}

int		remove_var(t_parsing_tool *tool, int i, char *env_name)
{
	char	*newstr;
	int		len_newstr;
	int		j;

	tool->empty_var = 0;
	j = 0;
	len_newstr = ft_strlen(tool->input) - (ft_strlen(env_name) + 1);
	if (!(newstr = malloc(sizeof(char) * (len_newstr + 1))))
		return (0);
	if (i > 0)
		ft_strncpy(newstr, tool->input, i);
	j = i + 1 + ft_strlen(env_name);
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}
