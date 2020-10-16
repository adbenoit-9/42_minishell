/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/16 14:28:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isredirect(t_stock **cmd_lst, int *fd_in, int *fd_out)
{
	if ((*cmd_lst)->sep == RIGHT)
	{
		*fd_in = open((*cmd_lst)->next->input[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if ((*cmd_lst)->stdin)
			*fd_out = open((*cmd_lst)->stdin[0], O_RDONLY);
	}
	else if ((*cmd_lst)->sep == LEFT)
		*fd_out = open((*cmd_lst)->next->input[0], O_RDONLY);
	else
		return (0);
	if (*fd_in != -1 && *fd_out != -1)
		return (1);
	return (-1);
}

int		ft_redirect(t_stock **cmd_lst, int *fd_in, int *fd_out)
{
	int fd[2];
	int	ret;

	fd[0] = 1;
	fd[1] = 1;
	if (fd_in)
		*fd_in = fd[0];
	if (fd_out)
		*fd_out = fd[1];
	if ((ret = ft_isredirect(cmd_lst, &fd[0], &fd[1])) == -1)
		return (-1);
	if (ret == 0)
		return (0);
	if (fd_in)
		*fd_in = fd[0];
	if (fd_out)
		*fd_out = fd[1];
	if ((*cmd_lst)->sep == (*cmd_lst)->next->sep)
		return (-1);
	if ((*cmd_lst)->sep == LEFT && (*cmd_lst)->next->sep == RIGHT)
		return (-1);
	return (0);
}
