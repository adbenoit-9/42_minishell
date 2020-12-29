/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/29 12:08:02 by adbenoit         ###   ########.fr       */
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

static int	is_executable(char *pwd, char *args[], char *envp[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	if (execve(pwd, args, envp) != -1)
		return (0);
	ret = 0;
	if (!ft_getenv("PATH", &ret, envp))
		return (-1);
	path = ft_split(envp[ret], ':');
	i = 0;
	ret = 0;
	while (path[i])
	{
		add_p = ft_strjoin(path[i++], "/");
		new_p = ft_strjoin(add_p, pwd);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
			ret = -1;
		free(new_p);
	}
	ft_free(path);
	return (ret);
}

static char	*join_path(char *path)
{
	char	*pwd;
	char	*new;

	if (ft_strncmp(path, "./", 2) == 0)
	{
		pwd = getcwd(NULL, 0);
		new = ft_strjoin(pwd, path + 1);
		return (new);
	}
	return (ft_strdup(path));
}

void		ft_not_builtin(t_cmd *cmd, int *fd, char *envp[])
{
	int		ret;
	int		i;
	char	*copy;
	char	**args;
	t_list	*tmp;

	i = 0;
	if (!cmd->tok || !(cmd->tok->content[0]))
		return ;
	if (!(args = (char **)malloc(sizeof(char *) * (ft_lstsize(cmd->tok) + 1))))
	{
		errno_msg(NULL, NULL, MALL_ERR, 0);
		return ;
	}
	tmp = cmd->tok;
	while (tmp)
	{
		args[i] = tmp->content;
		tmp = tmp->next;
		++i;
	}
	args[i] = NULL;
	i = -1;
	copy = join_path(cmd->tok->content);
	modify_fd(cmd, fd);
	ret = is_executable(copy, args, envp);
	free(copy);
	while (ret == -1 && cmd->tok->content[++i])
	{
		if (cmd->tok->content[i] == '/')
		{
			g_status = errno_msg(cmd->tok->content, NULL, 127, ENOENT);
			free(tmp);
			exit(g_status);
		}
	}
	if (ret == -1)
	{
		error_msg("\0", cmd->tok->content, ": command not found\n", 127);
		free(tmp);
		exit(g_status);
	}
}
