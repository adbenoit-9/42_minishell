/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/29 11:11:29 by adbenoit         ###   ########.fr       */
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

static int	is_executable(t_cmd *cmd, char *args[], int *fd, char *envp[])
{
	int		ret;
	int		i;
	char	**path;
	char	*add_p;
	char	*new_p;

	modify_fd(cmd, fd);
	if (execve(args[0], args, envp) != -1)
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
		new_p = ft_strjoin(add_p, args[0]);
		free(add_p);
		if (execve(new_p, args, envp) == -1)
			ret = -1;
		free(new_p);
	}
	ft_free(path);
	return (ret);
}

static char	*join_path(char **path)
{
	char	*pwd;
	char	*new;

	if (ft_strncmp(*path, "./", 2) == 0)
	{
		pwd = getcwd(NULL, 0);
		new = ft_strjoin(pwd, *path + 1);
		pwd = *path;
		*path = new;
		return (pwd);
	}
	return (*path);
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
	copy = join_path(&cmd->tok->content);
	ret = is_executable(cmd, args, fd, envp);
	while (ret == -1 && cmd->tok->content[++i])
	{
		if (cmd->tok->content[i] == '/')
		{
			g_status = errno_msg(copy, NULL, 127, ENOENT);
			free(tmp);
			exit(g_status);
		}
	}
	if (ret == -1)
	{
		error_msg("\0", copy, ": command not found\n", 127);
		free(tmp);
		exit(g_status);
	}
}
