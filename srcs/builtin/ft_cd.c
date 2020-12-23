/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 01:59:59 by adbenoit         ###   ########.fr       */
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
	if (!((*cmd)->tokens = ft_realloc_tab((*cmd)->tokens, 3)))
		return (errno_msg(NULL, NULL, MALL_ERR));
	if (!((*cmd)->tokens[1] = ft_strdup(envp[pos] + 5)))
		return (errno_msg(NULL, NULL, MALL_ERR));
	(*cmd)->tokens[2] = NULL;
	return (0);
}

void		ft_cd(t_cmd **cmd, int *fd, char *envp[])
{
	char	*path;
	int		pos;

	(void)fd;
	if (!(*cmd)->tokens[1] && cd_without_arg(cmd, envp) < 0)
		return ;
	g_tmp = check_path((*cmd)->tokens[1]);
	chdir((const char *)(*cmd)->tokens[1]);
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
		errno_msg("cd", (*cmd)->tokens[1], 0);
	return ;
}
