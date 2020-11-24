/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:12:42 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/24 16:23:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stock		*g_cmd;
t_shell	g_shell;

void    init_mshell(void)
{
	g_shell.pid = 0;
	g_shell.bool = 0;
}

void	ft_sig_handler(int signo)
{
	if (g_shell.pid == 0)
	{
		write(1, "\b\b  \b\b\n\033[1mLesPetitsCoquillages\033[0m", 35);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		g_shell.pid = 1;
	}
	else
	{
		kill(0, signo);
		g_shell.pid = 0;
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	char	*str;
	int		ret;
	size_t	i;

	if (argc > 1)
	{
		print_error(": ", argv[1], ": No argument requiered\n", 127);
		exit(g_status);
	}
	ret = 1;
	while (ret > 0)
	{
		init_mshell();
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_handler);
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		str = NULL;
		ret = get_next_line(0, &str);
		if (ret == 0)
            g_shell.bool = 0;
		g_cmd = NULL;
		i = 0;
		while (str[i] == ' ')
			++i;
		if (str[i] && parse_str(str + i) == 0)
		{
			parsing(str, envp);
			ft_stockclear(&g_cmd, clear_one);
		}
		free(str);
	}
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}
