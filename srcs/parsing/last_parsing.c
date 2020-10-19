/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:24:38 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 19:38:54 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int set_input(t_stock **cmd_lst)
{
	int fd;

	errno = 0;
	fd = open((*cmd_lst)->next->tokens[0], O_RDONLY);
	if (fd == -1)
	{
		write_error((*cmd_lst)->next->tokens[0], ": ", strerror(errno));
		write(1, "\n", 1);
		close(fd);
		return (-2);
	}
	close(fd);
	return (0);
}

static int set_output(t_stock **cmd_lst)
{
	int fd;

	errno = 0;
	fd = open((*cmd_lst)->next->tokens[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		write_error((*cmd_lst)->next->tokens[0], ": ", strerror(errno));
		write(1, "\n", 1);
		close(fd);
		return (-2);
	}
	close(fd);
	return (0);
}

int	last_parsing(t_stock **cmd_lst, int *i)
{
	int	ret;

	ret = 0;
	if (!(*cmd_lst)->next)
	{
		ret = sep_error(NONE, (*cmd_lst)->sep);
		return (ret);
	}
	else if ((*cmd_lst)->next->cmd == UNKNOW && !(*cmd_lst)->next->tokens[0][0])
	{
		sep_error((*cmd_lst)->next->sep, (*cmd_lst)->sep);
		return (-1);
	}
	if ((*cmd_lst)->sep == LEFT)
		ret = set_input(cmd_lst);
	else if ((*cmd_lst)->sep == RIGHT || (*cmd_lst)->sep == D_RIGHT)
		ret = set_output(cmd_lst);
	if ((*cmd_lst)->sep == COMA || (*cmd_lst)->sep == PIPE)
		++(*i);
	if ((*cmd_lst)->next && ret == 0)
		return (last_parsing(&(*cmd_lst)->next, i));
	return (ret);
}