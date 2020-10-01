/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:58:13 by celestin          #+#    #+#             */
/*   Updated: 2020/10/01 22:17:59 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		arg_cleanup(char **arg)
{
	int	ret;

	if ((ret = check_var(arg)) < 1)
		return (ret);
	if (!check_g_ret_var(arg))
		return (0);
	if (!ft_clean_bs_quote(arg))
		return (0);
	return (1);
}
