/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/25 13:48:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_try_path(t_stock **cmd_lst, char *envp[], char *args[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;
	int		fd[2];

	if (ft_redirect(cmd_lst, &fd[0], &fd[1]) == -1)
		return (-1);
	if ((*cmd_lst)->sep == RIGHT)
		dup2(fd[0], 1);
	if ((*cmd_lst)->sep == LEFT || (*cmd_lst)->stdin)
		dup2(fd[1], 0);
	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	while (path[i])
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
	return (0);
}

int		ft_launch_process(t_stock **cmd_lst, char *cmd, char *envp[])
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**args;

	pid = fork();
	ret = 0;
	args = ft_split(cmd, ' ');
	if (pid == 0)
	{
		ret = ft_try_path(cmd_lst, envp, args);
		exit(0);
	}
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

	ret = 0;
	i = 0;
	printf("%s, %d\n", (*cmd_lst)->input, (*cmd_lst)->sep);
	if (sep_error(cmd_lst) == 1)
		return ;
	else if ((ret = ft_launch_process(cmd_lst, (*cmd_lst)->input, envp)) == 0)
	{
		while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '/')
			++i;
		if ((size_t)i < ft_strlen((*cmd_lst)->input))
			write_error("\0", (*cmd_lst)->input,
			": No such file or directory\n");
		else
			write_error("\0", (*cmd_lst)->input, ": command not found\n");
	}
}
