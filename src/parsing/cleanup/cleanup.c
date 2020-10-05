/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:58:13 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 12:37:38 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		arg_cleanup(t_cmd *cmd)
{
	int	ret;

	if ((ret = check_var(cmd->arg)) < 1)
		return (ret);
	if (!check_space_var(cmd))
		return (0);
	if (!check_g_ret_var(cmd->arg))
		return (0);
	if (!ft_clean_bs_quote(cmd->arg))
		return (0);
	return (1);
}
