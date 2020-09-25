/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:24:38 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/25 17:01:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_parsing(t_stock **cmd_lst)
{
	int	fd;

	fd = -2;
	if ((*cmd_lst)->cmd == UNKNOW)
	{
		if (sep_error(cmd_lst) == 1)
			return (-1);
	}
	if ((*cmd_lst)->sep == RIGHT || (*cmd_lst)->sep == LEFT)
	{
		if (!(*cmd_lst)->next)
		{
			write_error("", "", "syntax error near unexpected token `newline'\n");
			return (-2);
		}
		else if ((*cmd_lst)->sep == LEFT)
			fd = open((*cmd_lst)->next->input, O_RDONLY);
		else if ((*cmd_lst)->sep == RIGHT)
			fd = open((*cmd_lst)->next->input, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if (fd == -1)
		{
			if ((*cmd_lst)->next->input[0] == '/')
				write_error("", (*cmd_lst)->next->input, ": Permission denied\n");
			else
				write_error("", (*cmd_lst)->next->input, ": No such file or directory\n");
			close(fd);
			return (-2);
		}
		if (fd != -2)
			close(fd);
	}
	if ((*cmd_lst)->next)
		return (last_parsing(&(*cmd_lst)->next));
	return (0);
}