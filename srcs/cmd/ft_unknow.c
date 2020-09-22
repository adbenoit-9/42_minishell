/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/22 16:25:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_try_path(char *envp[], char *args[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	while (path[i] != '\0')
	{
		add_p = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
		{
			free(new_p); //il faut free le bon
			i++;
		}
		else
			return (1);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_launch_process(char *cmd, char *envp[])
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**args;

	pid = fork();
	ret = 0;
	args = ft_split(cmd, ' ');
	if (pid == 0)
		ret = ft_try_path(envp, args);
	else if (pid < 0)
		return (ret);
	else
	{
		ret = 1;
		wait(&status);
	}
	return (ret);
}

void	ft_unknow(t_stock **cmd_lst, char *envp[])
{
	int	ret;
	int	i;

	if ((*cmd_lst)->input[0] == '<' || (*cmd_lst)->input[0] == '>')
		write_error("", "", "syntax error near unexpected token `newline'\n");
	else if (ft_issep((*cmd_lst)->input[0], 0) == 1)
	{
		write_error("", "syntax error near unexpected token `", "");
		if ((*cmd_lst)->input[1] == (*cmd_lst)->input[0])
			write(1, (*cmd_lst)->input, 2);
		else
			write(1, (*cmd_lst)->input, 1);
		write(1, "'\n", 2);
	}
	else if ((ret = ft_launch_process((*cmd_lst)->input, envp)) == 0)
	{
		i = 0;
		while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '/')
			++i;
		if ((size_t)i < ft_strlen((*cmd_lst)->input))
			write_error("\0", (*cmd_lst)->input,
			": No such file or directory\n");
		else
			write_error("\0", (*cmd_lst)->input, ": command not found\n");
	}
}
