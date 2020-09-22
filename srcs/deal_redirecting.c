/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirecting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:40:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/22 15:33:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		right_redirect(t_stock **cmd_lst)
{
	int	fd;

	fd = -1;
	if ((*cmd_lst)->sep == RIGHT)
	{
		if (!(*cmd_lst)->next)
			write_error("", "", "syntax error near unexpected token `newline'\n");
		else
		{
			fd = open((*cmd_lst)->next->input, O_CREAT | O_WRONLY | O_TRUNC, 0755);
			if (fd == -1 && (*cmd_lst)->next->input[0] == '/')
				write_error("", (*cmd_lst)->next->input, ": Permission denied\n");
			else if (fd == -1)
				write_error("", (*cmd_lst)->next->input, ": No such file or directory\n");
		}
	}
	return (fd);
}