/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/17 23:55:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** besoin d'un retour ?
*/

int		ft_try_path(t_stock *cmd, char *envp[], char *args[], int *fd)
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	if (cmd->output)
		dup2(fd[1], 1);
	if (cmd->input)
		dup2(fd[0], 0);
	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	ret = 0;
	while (path[i])
	{
		add_p = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
			ret = -1;
		++i;
		free(new_p);
	}
	ft_free(path);
	return (ret);
}

void	ft_unknow(t_stock **cmd, char *envp[], int *fd)
{
	int	ret;
	int	i;

	i = -1;
	(void)envp;
	while ((*cmd)->tokens[0][++i])
	{
		if ((*cmd)->tokens[0][i] == '/')
		{
			print_error("\0", (*cmd)->tokens[0],
			": No such file or directory\n", 127);
			return ;
		}
	}
	ret = ft_try_path(*cmd, envp, (*cmd)->tokens, fd);
	if (ret == -1)
	{
		print_error("\0", (*cmd)->tokens[0], ": command not found\n", 127);
		exit(EXIT_FAILURE);
	}
}
