/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 19:12:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirect(t_stock **g_cmd, int *fd_in, int *fd_out)
{
	if ((*g_cmd)->output && *fd_out)
	{
		if ((*g_cmd)->r_type == RIGHT)
		{
			*fd_out = open((*g_cmd)->output, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else
		{
			*fd_out = open((*g_cmd)->output, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
			S_IRGRP | S_IWGRP | S_IWUSR);
		}
	}
	if ((*g_cmd)->input && fd_in)
		*fd_in = open((*g_cmd)->input, O_RDONLY);
	return (0);
}
