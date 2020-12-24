/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 20:56:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *str)
{
	int	i;
	int	count;
	int	ret;

	i = -1;
	count = 0;
	while (str[++i] == '/')
		++count;
	ret = ft_strncmp("tmp", str + i, 3);
	if (ret != 0 && count == 2)
		return (3);
	else if (ret == 0 && count == 2)
		return (2);
	else if (ret == 0)
		return (1);
	return (0);
}

char		*ft_correct_path(char *path)
{
	if (g_tmp == 1)
		return (ft_strdup(path + 8));
	else if (g_tmp == 2)
		return (ft_strjoin("/", path + 8));
	else if (g_tmp == 3)
		return (ft_strjoin("/", path));
	return (ft_strdup(path));
}

static int	cd_without_arg(t_cmd **cmd, char *envp[])
{
	int	pos;

	if (!ft_getenv("HOME", &pos, envp))
	{
		error_msg("cd : ", "HOME not set\n", NULL, 1);
		return (-1);
	}
	(*cmd)->tok->next = ft_lstnew(ft_strdup(envp[pos] + 5));
	if (!((*cmd)->tok->next->content))
		return (errno_msg(NULL, NULL, MALL_ERR));
	return (0);
}

void		ft_cd(t_cmd *cmd, int *fd, char *envp[])
{
	char	*path;
	int		pos;

	(void)fd;
	if (!cmd->tok->next->content && cd_without_arg(&cmd, envp) < 0)
		return ;
	g_tmp = check_path(cmd->tok->next->content);
	chdir((const char *)cmd->tok->next->content);
	path = getcwd(NULL, 0);
	if (errno == 0)
	{
		path = ft_correct_path(path);
		if (!ft_getenv("PWD", &pos, envp))
			ft_setenv("OLDPWD", envp[pos] + 4, 0, envp);
		else
			ft_setenv("OLDPWD", "\'\'", 0, envp);
		ft_setenv("PWD", path, 0, envp);
		free(path);
	}
	if (errno != 0)
		errno_msg("cd", cmd->tok->next->content, 0);
	return ;
}
