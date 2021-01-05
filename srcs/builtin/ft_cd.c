/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 22:34:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] == '/')
		++count;
	if (count == 2)
		return (2);
	return (0);
}

char		*ft_correct_path(char *path)
{
	char	*new;

	if (g_tmp == 2)
	{
		new = ft_strjoin("/", path);
		free(path);
		return (new);
	}
	return (path);
}

static int	ft_cd_home(t_cmd **cmd, char *envp[])
{
	int	pos;

	pos = 0;
	if ((*cmd)->tok->next && (*cmd)->tok->next->content)
		return (0);
	else if ((*cmd)->tok->next)
		free((*cmd)->tok->next);
	if (!ft_getenv("HOME", &pos, envp))
	{
		error_msg("cd: ", "HOME not set\n", NULL, 1);
		return (-1);
	}
	if (!((*cmd)->tok->next = ft_lstnew(ft_strdup(envp[pos] + 5)))
	|| !((*cmd)->tok->next->content))
		return (errno_msg(NULL, NULL, MALL_ERR));
	return (1);
}

void		ft_no_err(char **path, int *pos, char **envp[])
{
	if (!(*path = ft_correct_path(*path)))
	{
		errno_msg(NULL, NULL, MALL_ERR);
		return ;
	}
	free(g_shell.pwd);
	g_shell.pwd = *path;
	*pos = 0;
	if (ft_getenv("PWD", pos, *envp))
		ft_setenv("OLDPWD", (*envp)[*pos] + 4, 0, envp);
	else
		ft_setenv("OLDPWD", "", 0, envp);
	ft_setenv("PWD", *path, 0, envp);
}

void		ft_cd(t_cmd *cmd, int *fd, char **envp[])
{
	char	*path;
	int		pos;

	(void)fd;
	if (ft_cd_home(&cmd, *envp) == -1)
		return ;
	g_tmp = check_path(cmd->tok->next->content);
	if (chdir((const char *)cmd->tok->next->content) == 0)
		path = getcwd(NULL, 0);
	if (errno == 0)
		ft_no_err(&path, &pos, envp);
	else
		errno_msg("cd", cmd->tok->next->content, 0);
}
