/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:05:46 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/18 16:31:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch_cmd(t_stock **cmd_lst, char *envp[])
{
	int	fd;
	char *err;

	err = NULL;
	if ((*cmd_lst)->sep == COMA || (*cmd_lst)->sep == NONE)
	{
		if ((*cmd_lst)->output)
			write(1, (*cmd_lst)->output, ft_strlen((*cmd_lst)->output));
	}
	if ((*cmd_lst)->cmd == ECHO && (*cmd_lst)->sep == RIGHT)
	{
		if (!(*cmd_lst)->next)
			err = output_error("", "", "syntax error near unexpected token `newline'\n");
		else
		{
			fd = open((*cmd_lst)->next->input, O_CREAT | O_WRONLY | O_TRUNC, 0755);
			if (fd == -1 && (*cmd_lst)->next->input[0] == '/')
				err = output_error("", (*cmd_lst)->next->input, ": Permission denied\n");
			else if (fd == -1)
				err = output_error("", (*cmd_lst)->next->input, ": No such file or directory\n");
			write(fd, (*cmd_lst)->input, ft_strlen((*cmd_lst)->input));
			close(fd);
		}
		if (err)
			write(1, err, ft_strlen(err));
		if ((*cmd_lst)->next && (*cmd_lst)->next->next)
			return (execute(&(*cmd_lst)->next->next, envp));
		else
			return (0);
		
	}
	if ((*cmd_lst)->next)
		return (execute(&(*cmd_lst)->next, envp));
	return (0);
}