/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/10 00:38:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirect(t_stock **cmd, int *fd_in, int *fd_out)
{
	if ((*cmd)->output && *fd_out)
	{
		if ((*cmd)->r_type == RIGHT)
		{
			*fd_out = open((*cmd)->output, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else
		{
			*fd_out = open((*cmd)->output, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
	}
	if ((*cmd)->input && fd_in)
		*fd_in = open((*cmd)->input, O_RDONLY);
	return (0);
}
