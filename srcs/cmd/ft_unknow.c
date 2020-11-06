/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:33:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// besoin d'un retour ?
int		ft_try_path(t_stock **g_cmd, char *envp[], char *args[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;
	int		fd[2];

	fd[0] = 1;
	fd[1] = 1;
	ft_redirect(g_cmd, &fd[0], &fd[1]);
	if ((*g_cmd)->output)
		dup2(fd[1], 1);
	if ((*g_cmd)->input)
		dup2(fd[0], 0);
	ret = find_var(envp, "PATH");
	path = ft_split(envp[ret], ':');
	i = 0;
	ret = 0;

	int j = 0;
	while (args[j] && args[j][0])
		j++;
	args[j] = NULL;
	//
	while (path[i])
	{
		add_p = ft_strjoin(path[i], "/");
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
		{
			ret = -1;
			free(new_p);
			i++;
		}
		else
		{
			// free path
			free(new_p);
			//return(1);
		}
	}
	// free path
	return(ret);
}

void	ft_unknow(t_stock **g_cmd, char *envp[])
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	errno = 0;
	(void)envp;
	ft_loop_pipe(g_cmd, envp);
	if (ret == -1)
	{
		while ((*g_cmd)->tokens[0][i] && (*g_cmd)->tokens[0][i] != '/')
			++i;
		if ((size_t)i < ft_strlen((*g_cmd)->tokens[0]))
			write_error("\0", (*g_cmd)->tokens[0],
			": No such file or directory\n", 1);
		else
			write_error("\0", (*g_cmd)->tokens[0], ": command not found\n", 127);
		exit(EXIT_FAILURE);
	}
	if (errno != 0)
		g_status = 1;
	else
		g_status = 0;
	g_status = 0;
}
