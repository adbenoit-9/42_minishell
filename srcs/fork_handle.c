/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:53:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/22 15:30:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_son(t_cmd *cmd, int *fd, int *p, char *envp[])
{
	g_shell.pid = 1;
	g_shell.bool = 0;
	dup2(fd[0], 0);
	if (cmd->next)
		dup2(p[1], 1);
	close(p[0]);
	run_cmd(cmd, envp, fd, 0);
	exit(EXIT_SUCCESS);
}

static void	set_status(int n, int pid)
{
	int	status;

	status = 0;
	while (n-- >= 0)
	{
		if (wait(&status) == pid)
		{
			g_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status) == 1)
				g_status = 128 + WTERMSIG(status);
		}
	}
}

void		ft_fork_handle(t_cmd *cmd, char *envp[])
{
	int		p[2];
	int		fd[2];
	int		nb_wait;
	pid_t	pid;

	nb_wait = -1;
	fd[0] = 1;
	fd[1] = 1;
	while (cmd)
	{
		ft_mana_sig(cmd);
		if (pipe(p) == -1 || (pid = fork()) == -1)
			exit(errno_msg(NULL, NULL, EXIT_FAILURE));
		if (pid == 0)
			ft_son(cmd, fd, p, envp);
		else
		{
			run_cmd(cmd, envp, fd, 1);
			close(p[1]);
			fd[0] = p[0];
		}
		cmd = cmd->next;
		nb_wait++;
	}
	set_status(nb_wait, pid);
}
