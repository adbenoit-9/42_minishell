/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/09 13:39:21 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stock		*g_cmd;
t_mshell	g_mshell;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\b\b  \b\b\n\033[1mLesPetitsCoquillages\033[0m", 35);
 		write(2, "\xF0\x9F\x90\x9A: ", 6);
		signal(SIGINT, signal_handler);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	int		ret;
	size_t	i;

	(void)argc;
	(void)argv;
	while (1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
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
