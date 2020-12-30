/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:12:42 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/29 23:59:03 by adbenoit         ###   ########.fr       */
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

static int	read_from_str(int n, char **argv, char **str)
{
	int	i;

	if (n > 2)
	{
		i = 2;
		*str = ft_strdup(argv[2]);
		while (*str && argv[++i])
		{
			*str = ft_strjoin(*str, ";");
			*str = ft_strjoin(*str, argv[i]);
		}
	}
	else
		*str = ft_strdup("\0");
	if (!*str)
		return (-1);
	return (0);
}

static int	display_prompt(int n, char **argv, char **str)
{
	int	ret;

	ret = 1;
	init_mshell();
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
	if (n == 1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		*str = NULL;
		ret = get_next_line(0, str);
	}
	else
		ret = read_from_str(n, argv, str);
	if (ret == -1)
		return (errno_msg(NULL, NULL, MALL_ERR));
	return (ret);
}

static int	launch_mshell(char *str, int n, char *envp[], int ret)
{
	int i;

	i = 0;
	g_cmd = NULL;
	if (ret == 0)
		g_shell.bool = 0;
	if (!envp)
		exit(errno_msg("envp :", NULL, MALL_ERR));
	while (str[i] == ' ')
		++i;
	if (str[i] && parse_syntax(str + i) == 0)
	{
		parsing(str, envp);
		free(str);
	}
	if (n > 1)
		exit(g_status);
	return (0);
}

int			main(int argc, char *argv[], char **envp)
{
	char	*str;
	int		ret;
	int		i;

	ret = 1;
	errno = 0;
	if (argc > 1 && ft_strcmp(argv[1], "-c") != 0)
	{
		errno = EINVAL;
		exit(errno_msg(argv[1], NULL, 127));
	}
	i = -1;
	while (envp[++i])
		envp[i] = ft_strdup(envp[i]);
	while (ret > 0)
	{
		str = NULL;
		if ((ret = display_prompt(argc, argv, &str)) == -1)
			return (0);
		launch_mshell(str, argc, envp, ret);
		free(str);
	}
	write(1, "exit\n", 5);
	ft_cmdclear(&g_cmd, clear_one);
	exit(EXIT_SUCCESS);
}
