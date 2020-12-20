/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/20 17:31:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*tmp;

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
	char	*path;
	int		pos;

	(void)fd;
	if (!(*cmd)->tokens[1] && without_arg(cmd, envp) < 0)
		return ;
	if (!(path = correct_path((*cmd)->tokens[1])))
		return ;
	chdir((const char *)path);
	if (errno == 0)
	{
		ft_tmp(path);
		if((pos = find_var(envp, "PWD")) != VAR_NOT_FOUND)
			modify_pwd(envp[pos] + 4, envp, "OLDPWD");
		else
			modify_pwd("\'\'", envp, "OLDPWD");
		modify_pwd(path, envp, "PWD");
	}
	if (errno != 0)
		errno_msg("cd", (*cmd)->tokens[1], 0);
	return ;
}
