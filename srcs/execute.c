/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:24:24 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/17 22:26:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_stock *cmd, char *envp[], int *fd, int pid)
{
	int					i;
	static t_function	cmd_fct[NUM_CMD + 1] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit, ft_unknow};
	static char			*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

	g_status = 0;
	errno = 0;
	if (cmd && cmd->tokens[0])
	{
		i = 0;
		while (i < NUM_CMD && ft_strcmp(cmd_str[i], cmd->tokens[0]) != 0)
			++i;
		if ((i < UNKNOW && ((pid == 0 && cmd->sep == PIPE) ||
		(pid == 1 && cmd->sep != PIPE))) || (i == UNKNOW && pid == 0))
		{
			ft_redirect(&cmd, &fd[1], &fd[1]);
			cmd_fct[i](&cmd, envp, fd);
		}
	}
	if (fd[0] != 1)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	return (0);
}
