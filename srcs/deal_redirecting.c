/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/23 17:47:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirect(t_stock **cmd_lst, int *fd_in, int *fd_out)
{
	int fd[2];

	fd[0] = 1;
	fd[1] = 1;
	if ((*cmd_lst)->sep != NONE && (*cmd_lst)->sep != COMA)
	{
		if (!(*cmd_lst)->next)
		{
			write_error("", "", "syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else
		{
			if ((*cmd_lst)->sep == RIGHT)
				fd[0] = open((*cmd_lst)->next->input, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if ((*cmd_lst)->sep == LEFT)
				fd[1] = open((*cmd_lst)->next->input, O_RDONLY);
			if ((fd[0] == -1 || fd[1] == -1) && (*cmd_lst)->next->input[0] == '/')
				write_error("", (*cmd_lst)->next->input, ": Permission denied\n");
			else if (fd[0] == -1 || fd[1] == -1)
				write_error("", (*cmd_lst)->next->input, ": No such file or directory\n");
		}
		if (fd[0] == -1 || fd[1] == -1)
			return (-1);
		if (fd_in)
			*fd_in = fd[0];
		if (fd_out)
			*fd_out = fd[1];
	}
	return (0);
}
