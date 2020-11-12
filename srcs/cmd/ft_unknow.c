/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/12 16:09:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** besoin d'un retour ?
*/

int		ft_try_path(char *envp[], char *args[], int *fd)
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	dup2(fd[1], 1);
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

	ret = 0;
	i = 0;
	(void)envp;
	ft_loop_pipe(cmd, envp, fd);
	if (ret == -1)
	{
		while ((*cmd)->tokens[0][i] && (*cmd)->tokens[0][i] != '/')
			++i;
		if ((size_t)i < ft_strlen((*cmd)->tokens[0]))
			print_error("\0", (*cmd)->tokens[0],
			": No such file or directory\n", 1);
		else
			print_error("\0", (*cmd)->tokens[0], ": command not found\n", 127);
		exit(EXIT_FAILURE);
	}
}
