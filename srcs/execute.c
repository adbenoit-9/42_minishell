/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:24:24 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/09 11:58:33 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_stock *cmd, char *envp[])
{
	int					i;
	static t_function	cmd_fct[NUM_CMD + 1] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit, ft_unknow};
	static char			*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};
	int					fd[2];

	i = 0;
	g_status = 0;
	errno = 0;
	fd[0] = 1;
	fd[1] = 1;
	ft_redirect(&cmd, &fd[1], &fd[1]);
	if (cmd)
	{
		if (!cmd->tokens[0])
			return (0);
		while (i < NUM_CMD)
		{
			if (ft_strcmp(cmd_str[i], cmd->tokens[0]) == 0)
				break;
			++i;
		}
		cmd_fct[i](&cmd, envp, fd);
	}
	if (fd[0] != 1)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	return (0);
}