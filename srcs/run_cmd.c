/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:24:24 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/30 19:46:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(t_cmd *cmd, int *fd, int pid, char **envp[])
{
	int					i;
	static t_function	cmd_fct[NUM_CMD + 1] = {ft_echo, ft_cd, ft_pwd, ft_env,
								ft_export, ft_unset, ft_exit, ft_not_builtin};
	static char			*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

	i = 0;
	if (cmd && cmd->tok && cmd->tok->content)
	{
		while (i < NUM_CMD && ft_strcmp(cmd_str[i], cmd->tok->content) != 0)
			++i;
		if ((i < UNKNOW && ((pid == 0 && cmd->sep == PIPE) ||
		(pid == 1 && cmd->sep != PIPE))) || (i == UNKNOW && pid == 0))
		{
			g_status = 0;
			errno = 0;
			ft_redirect(cmd, &fd[0], &fd[1]);
			cmd_fct[i](cmd, fd, envp);
		}
	}
	if (fd[0] != 1)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	return (i);
}
