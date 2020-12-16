/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/16 21:24:49 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_old_tmp(char *old)
{
	if (ft_strcmp(old, "/private/tmp") == 0)
	{
		if (g_tmp == 1)
			ft_strcpy(old, "/tmp");
		else if (g_tmp == 2)
			ft_strcpy(old, "//tmp");
	}
	return ;
}

void			ft_tmp(char *path)
{
	g_tmp = check_tmp(path);
	if (g_tmp == 1)
		strcpy(path, "/tmp");
	else if (g_tmp == 2)
		strcpy(path, "//tmp");
	return ;
}
int		modify_pwd(char *path, char *envp[], char *var)
{
	int		pos;
	size_t	size;
	char	*tmp;

	size = 0;
	if (!path)
		path = getcwd(NULL, size);
	if ((pos = find_var(envp, var)) == VAR_NOT_FOUND)
	{
		tmp = ft_strjoin(var, "=");
		path = ft_strjoin(tmp, path);
		free(tmp);
		ft_add_to_envp(envp, path);
	}
	else
		ft_modify_envp(envp, var, path, pos);
	return (0);
}

void			ft_cd(t_stock **cmd, char *envp[], int *fd)
{
	char	old[4098];
	char	*path;

	(void)fd;
	if (!(*cmd)->tokens[1] && without_arg(cmd, envp) < 0)
		return ;
	if (!(path = correct_path((*cmd)->tokens[1])))
		return ;
	getcwd(old, 0); // pas comme ca, faut remplacer par la variable PWD + voir prob unset PWD
	chdir((const char *)path);
	if (errno == 0)
	{
		ft_old_tmp(old);
		ft_tmp(path);
		modify_pwd(old, envp, "OLDPWD");
		modify_pwd(NULL, envp, "PWD");
	}
	if (errno != 0)
		errno_msg("cd", (*cmd)->tokens[1], 0);
	return ;
}
