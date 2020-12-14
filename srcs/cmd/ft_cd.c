/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/14 17:46:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_no_tmp(char **now, char **tmp)
{
	char *bis;

	bis = NULL;
	if (!(bis = (char *)malloc(sizeof(char) * 5)))
		return ;
	if (g_tmp == 1)
		bis = ft_strcpy(bis, "/tmp");
	else if (g_tmp == 2)
		bis = ft_strcpy(bis, "//tmp");
	if (ft_strcmp(*now, "/private/tmp") == 0)
	{
		*tmp = (char *)malloc(sizeof(char) * 1);
		*tmp = ft_strcpy(*tmp, "/");
	}
	*now = bis;
	return ;
}

void			ft_tmp(char **now, char **path, char **tmp)
{
	if (ft_strcmp(*now, "/private/tmp") == 0 && g_tmp == 1)
		*now = strcpy(*now, "/tmp");
	if (ft_strcmp(*now, "/private/tmp") == 0 && g_tmp == 2)
		*now = strcpy(*now, "//tmp");
	if (check_tmp(*path) == 0)
		g_tmp = 0;
	else
	{
		*tmp = (char *)malloc(sizeof(char) * 5);
		if (check_tmp(*path) == 1)
		{
			*tmp = strcpy(*tmp, "/tmp");
			g_tmp = 1;
		}
		else if (check_tmp(*path) == 2)
		{
			*tmp = strcpy(*tmp, "//tmp");
			g_tmp = 2;
		}
	}
	return ;
}

void			ft_cd(t_stock **cmd, char *envp[], int *fd)
{
	char	*now;
	char	*path;
	char	*tmp;

	(void)fd;
	if (!(*cmd)->tokens[1] && without_arg(cmd, envp) < 0)
		return ;
	if (!(path = correct_path((*cmd)->tokens[1])))
		return ;
	now = getcwd(NULL, 0);
	chdir((const char *)path);
	tmp = NULL;
	if (errno == 0)
	{
		if (check_tmp(path) == 0)
			ft_no_tmp(&now, &tmp);
		else if (check_tmp(path) != 0)
			ft_tmp(&now, &path, &tmp);
		modify_pwd(now, envp, "OLDPWD");
		modify_pwd(tmp, envp, "PWD");
	}
	if (errno != 0)
		print_errno("cd", (*cmd)->tokens[1], 0);
	return ;
}
