/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 14:17:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirect(t_stock **cmd_lst, int *fd_in, int *fd_out)
{
	if ((*cmd_lst)->output && *fd_out)
	{
		if ((*cmd_lst)->r_type == RIGHT)
		{
			*fd_out = open((*cmd_lst)->output, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else
		{
			*fd_out = open((*cmd_lst)->output, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
			S_IRGRP | S_IWGRP | S_IWUSR);
		}
	}
	if ((*cmd_lst)->input && fd_in)
		*fd_in = open((*cmd_lst)->input, O_RDONLY);
	return (0);
}
