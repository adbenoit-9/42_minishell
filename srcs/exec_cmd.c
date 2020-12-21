/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/21 17:34:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_fd(t_cmd *cmd, int *fd)
{
	if (cmd->output)
		dup2(fd[1], 1);
	if (cmd->input)
		dup2(fd[0], 0);
}

static int	is_executable(t_cmd *cmd, char *envp[], char *args[], int *fd)
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	modify_fd(cmd, fd);
	if (execve(args[0], args, envp) != -1)
		return (0);
	if ((ret = find_var(envp, "PATH")) == VAR_NOT_FOUND)
		return (-1);
	path = ft_split(envp[ret], ':');
	i = 0;
	ret = 0;
	while (path[i])
	{
		add_p = ft_strjoin(path[i++], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
			ret = -1;
		free(new_p);
	}
	ft_free(path);
	return (ret);
}

void		ft_not_builtin(t_cmd **cmd, char *envp[], int *fd)
{
	int	ret;
	int	i;

	i = -1;
	if (!((*cmd)->tokens[0][0]))
		return ;
	ret = is_executable(*cmd, envp, (*cmd)->tokens, fd);
	while (ret == -1 && (*cmd)->tokens[0][++i])
	{
		if ((*cmd)->tokens[0][i] == '/')
		{
			error_msg("\0", (*cmd)->tokens[0],
			": No such file or directory\n", 127);
			return ;
		}
	}
	if (ret == -1)
	{
		error_msg("\0", (*cmd)->tokens[0], ": command not found\n", 127);
		exit(EXIT_FAILURE);
	}
}
