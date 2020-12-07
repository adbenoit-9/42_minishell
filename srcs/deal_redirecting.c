/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/03 16:21:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirect(t_stock **cmd)
{
	int	fd_in;
	int	fd_out;

	if ((*cmd)->output)
	{
		if ((*cmd)->r_type == RIGHT)
		{
			fd_out = open((*cmd)->output, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else
		{
			fd_out = open((*cmd)->output, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		dup2(fd_out, STDOUT_FILENO);
	}
	if ((*cmd)->input)
	{
		fd_in = open((*cmd)->input, O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
	}
	return (0);
}
