/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:54:27 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:22:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_handler(int signo)
{
	if (g_shell.pid == 0)
	{
		g_status = 130;
		ft_putstr_fd("\b\b  \b\b\n\033[35mminishell\033[0m", 1);
		ft_putstr_fd("\xF0\x9F\x90\x9A\033[35m: \033[0m", 1);
		g_shell.pid = 1;
	}
	else
	{
		kill(0, signo);
		g_shell.pid = 0;
	}
	return ;
}

void	proc_sig_handler(int signo)
{
	if (g_shell.pid == 0 && g_shell.bool == 1)
	{
		g_shell.pid = 1;
		g_shell.bool = 0;
	}
	else if (g_shell.pid == 0 && g_shell.bool == 0)
	{
		(void)signo;
		write(1, "\n", 1);
		kill(0, signo);
		g_shell.sig = 1;
		g_shell.pid = 1;
	}
	return ;
}

void	ft_mana_sig(t_cmd *cmd)
{
	if (cmd->tok && cmd->tok->content &&
	ft_strcmp(cmd->tok->content, "./minishell") == 0)
		g_shell.bool = 1;
	if (cmd->tok && cmd->tok->content &&
	ft_strcmp(cmd->tok->content, "exit") == 0)
	{
		g_shell.bool = 0;
		g_shell.pid = 1;
	}
	g_shell.sig = 0;
	signal(SIGINT, proc_sig_handler);
	signal(SIGQUIT, proc_sig_handler);
	g_shell.pid = 0;
}
