/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:12:42 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/29 17:57:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*g_cmd;
t_shell	g_shell;

void		init_mshell(void)
{
	g_shell.pid = 0;
	g_shell.bool = 0;
}

static int	display_prompt(int argc, char **argv, int *ret, char **str)
{
	int i;

	init_mshell();
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	if (argc == 1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		*str = NULL;
		*ret = get_next_line(0, str);
	}
	else if (argc > 2)
	{
		i = 2;
		*str = ft_strdup(argv[2]);
		while (argv[++i])
		{
			*str = ft_strjoin(*str, ";");
			*str = ft_strjoin(*str, argv[i]);
		}
		if (!str)
			return (0);
	}
	else
		*str = ft_strdup("\0");
	return (1);
}

static void	term(char *str, int argc, char **argv, char *envp[])
{
	int i;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (str[i] && parse_str(str + i) == 0)
	{
		parsing(str, envp);
		free(str);
		// ft_cmdclear(&g_cmd, clear_one);
	}
	if (argc > 1 && ft_strcmp(argv[1], "-c") == 0)
		exit(g_status);
	return ;
}

int		main(int argc, char *argv[], char **envp)
{
	char	*str;
	int		ret;

	str = NULL;
	ret = 1;
	errno = 0;
	if (argc > 1 && ft_strcmp(argv[1], "-c") != 0)
	{
		errno = EINVAL;
		exit(errno_msg(argv[1], NULL, 127));
	}
	int i = -1;
	while(envp[++i])
		envp[i] = ft_strdup(envp[i]);
	while (ret > 0)
	{
		if (display_prompt(argc, argv, &ret, &str) == 0)
			return (0);
		if (ret == 0)
			g_shell.bool = 0;
		g_cmd = NULL;
		term(str, argc, argv, envp);
	}
	free(str);
	write(1, "exit\n", 5);
	// ft_cmdclear(&g_cmd, clear_one);
	exit(EXIT_SUCCESS);
}
