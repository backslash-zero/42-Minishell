/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:16:10 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/10 18:20:32 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		expand_env(t_parsing_tool *tool)
{
	int i;

	i = 0;
	while (tool->input[i])
	{
		if (is_dollar(tool->input[i]) && !(tool->open && tool->quote == '\''))
		{
			if (!insert_env_var(tool, i))
				return (-1);
			if (is_quote(tool->input[i]))
				switcher_quote(tool, tool->input[i]);
		}
		i++;
	}
	return (0);
}

int		replace_var(t_parsing_tool *tool, int i, char *var, char *env_name)
{
	char *newstr;
	char *tmp;
	int j;
	
	j = 0;
	if (!(newstr = malloc(sizeof(char) * (i - 1 + ft_strlen(var) - (ft_strlen(env_name) + 1) + 1))))
		return (0);
	while (j < i)
	{
		newstr[j] = tool->input[j];
		j++;
	}
	j = 0;
	while (var[j] && tool->input[i])
	{
		newstr[i] = var[j];
		i++;
		j++;
	}
	i = i - ft_strlen(var) + ft_strlen(var) + 1;
	while (tool->input[i])
	{
		newstr[j] = tool->input[i];
		j++;
		i++;
	}
	newstr[j] = '\0';
	tmp = tool->input;
	tool->input = newstr;
	free(tmp);
	return (1);
}

int		insert_env_var(t_parsing_tool *tool, int i)
{
	char *env_name;
	char *var;

	printf("input: %s\n", tool->input);
	if (!(env_name = get_var_name(tool, i)))
		return (0);
	printf("var name:%s\n", env_name);
	if (!(var = parsing_variable(env_name)))
		return (0);
	printf("var: %s\n", var);
	replace_var(tool, i, var, env_name);
	printf("input: %s\n", tool->input);
	free(env_name);
	free(var);
	return(1);
}

char *get_var_name(t_parsing_tool *tool, int i)
{
	int j;
	int k;
	char *env_name;

	i++;
	j = i;
	k = 0;
	while (tool->input[j] && !is_quote(tool->input[j]) && !is_space(tool->input[j]) && !is_quote(tool->input[j]) && !is_dollar(tool->input[i]))
	{
		j++;
		k++;
	}
	if (!(env_name = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	k = 0;
	while (i < j)
	{
		env_name[k] = tool->input[i];
		i++;
		k++;
	}
	env_name[k] = '\0';
	return(env_name);
}

char	*parsing_variable(char *str)
{
	t_list	*tmp;
	char	*output;
	int len;

	len = ft_strlen(str);
	printf("len: %d\n", len);
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->content, len))
		{
			return (ft_strdup(&(tmp->content[len + 1])));
		}
		tmp = tmp->next;
	}
	return(ft_strdup(""));
}