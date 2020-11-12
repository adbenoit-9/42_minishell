/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/12 16:06:52 by adbenoit         ###   ########.fr       */
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

void    ft_sigint_handler(int signo)
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

	(void)argc;
	(void)argv;
	init_mshell();
	while (1)
	{
		signal(SIGINT, ft_sigint_handler);
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		str = NULL;
		ret = get_next_line(0, &str);
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
	return (0);
}
