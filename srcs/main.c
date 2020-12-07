/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:12:42 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/03 11:16:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stock	*g_cmd;
t_shell	g_shell;

void	init_mshell(void)
{
	g_shell.pid = 0;
	g_shell.bool = 0;
}

int		start(int argc, char **argv, int *ret, char **str)
{
	int i;

	init_mshell();
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	if (argc == 1 || (argc > 1 && ft_strcmp(argv[1], "-c") != 0))
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		*str = NULL;
		*ret = get_next_line(0, str);
	}
	else
	{
		i = 2;
		*str = ft_strjoin(argv[2], " ");
		while (argv[++i])
		{
			*str = ft_strjoin(*str, argv[i]);
			*str = ft_strjoin(*str, " ");
		}
		if (!str)
			return (0);
	}
	return (1);
}

void	term(char *str, char *envp[], int argc, char **argv)
{
	size_t i;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (str[i] && parse_str(str + i) == 0)
	{
		parsing(str, envp);
		ft_stockclear(&g_cmd, clear_one);
	}
	if (argc > 1 && ft_strcmp(argv[1], "-c") == 0)
		exit(g_status);
	return ;
}

int		main(int argc, char *argv[], char *envp[])
{
	char	*str;
	int		ret;

	str = NULL;
	ret = 1;
	if (argc > 1 && ft_strcmp(argv[1], "-c") != 0)
	{
		print_error(": ", argv[1], ": No argument requiered\n", 127);
		exit(g_status);
	}
	while (ret > 0)
	{
		if (start(argc, argv, &ret, &str) == 0)
			return (0);
		if (ret == 0)
			g_shell.bool = 0;
		g_cmd = NULL;
		term(str, envp, argc, argv);
	}
	write(1, "exit\n", 5);
	ft_stockclear(&g_cmd, clear_one);
	exit(EXIT_SUCCESS);
}
