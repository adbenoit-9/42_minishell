/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:55:33 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 13:58:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (-2);
	path = ft_split(envp[ret] + 5, ':');
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
	ft_freetab(path);
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
		free(pwd);
	}
	else
		new = ft_strdup(path);
	if (!new)
		errno_msg(NULL, NULL, MALL_ERR);
	return (new);
}

static int	exec_error(char *cmd, void *next)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
		{
			if (chdir(cmd) == 0)
				errno = EISDIR;
			errno = errno == ENOTDIR ? EACCES : errno;
			if (errno == EISDIR)
				error_msg(cmd, NULL, ": is a directory\n", 126);
			else
				g_status = errno_msg(cmd, NULL, 127);
			g_status = errno == EACCES ? 126 : g_status;
			return (g_status);
		}
		else if (cmd[i] == '.' && !cmd[i + 1] && !next)
			return (error_msg(cmd, NULL, "filename argument required\n\
			\r.:usage: . filename [arguments]\n", 2));
	}
	return (error_msg(cmd, NULL, ": command not found\n", 127));
}

int			ft_protec(t_cmd *cmd, char ***args)
{
	if (!cmd->tok->content || !cmd->tok->content[0])
		return (1);
	if (!(*args = (char **)malloc(sizeof(char *) * (ft_lstsize(cmd->tok) + 1))))
	{
		errno_msg(NULL, NULL, MALL_ERR);
		return (1);
	}
	return (0);
}

void		ft_not_builtin(t_cmd *cmd, int *fd, char **envp[])
{
	int		i;
	char	*copy;
	char	**args;
	t_list	*tmp;

	args = NULL;
	if (ft_protec(cmd, &args) == 1)
		return ;
	i = 0;
	tmp = cmd->tok;
	args[i++] = tmp->content;
	while ((tmp = tmp->next))
		args[i++] = tmp->content;
	args[i] = NULL;
	if (!(copy = join_path(cmd->tok->content)))
		return ;
	modify_fd(cmd, fd);
	i = is_executable(copy, args, *envp);
	free(copy);
	if (i == -2)
		error_msg(cmd->tok->content, NULL, ": No such file or directory\n", 1);
	else if (i == -1)
		g_status = exec_error(cmd->tok->content, cmd->tok->next);
	exit(g_status);
}
