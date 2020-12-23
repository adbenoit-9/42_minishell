/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:45:38 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 13:58:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *name, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '+' && str[i] != '=')
		++i;
	name = ft_strncpy(name, str, i);
	name[i] = 0;
	return (name);
}

static void ft_display(char *str, int fd)
{
	int		i;
	int		j;
	char	new[4096];

	if (!str || !str[0])
		return ;
	i = 0;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\\')
		{
			new[j] = '\\';
			++j;
		}
		new[j] = str[i];
		++j;
	}
	new[j] = 0;
	ft_putstr_fd(new, fd);
}

static void	ft_putenv_fd(char *token, int fd, char *envp[])
{
	char	**copy;
	char	var[4096];
	int		i;
	int		len;

	if (!token)
	{
		copy = ft_tabdup(envp);
		ft_sort_env(copy);
		i = -1;
		while (copy[++i])
		{
			get_var_name(var, copy[i]);
			len = ft_strlen(var);
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(var, fd);
			ft_putstr_fd( "=\"", fd);
			ft_display(copy[i] + len, fd);
			ft_putstr_fd( "\"\n", fd);
		}
		ft_free(copy);
		return ;
	}
}

void		ft_export(t_cmd **cmd, int *fd, char *envp[])
{
	int		i;
	int		len;
	char	var[4096];

	i = 0;
	while ((*cmd)->tokens[++i])
	{
		get_var_name(var, (*cmd)->tokens[i]);
		len = ft_strlen(var);
		if (check_var_name(var) == 0)
		{
			error_msg("export: `", (*cmd)->tokens[i],
			"\': not a valid identifier\n", 1);
			return ;
		}
		if ((*cmd)->tokens[i][len] == '+' && (*cmd)->tokens[i][len + 1] == '=')
			ft_setenv(var, (*cmd)->tokens[i] + len + 2, 1, envp);
		else if ((*cmd)->tokens[i][len] == '=')
			ft_setenv(var, (*cmd)->tokens[i] + len + 1, 0, envp);
		else if (!(*cmd)->tokens[i][len] && !ft_getenv((*cmd)->tokens[i], 0, envp))
		{
			len = ft_tabsize(envp);
			envp[len] = strdup(var);
			envp[len + 1] = 0;
		}
	}
	ft_putenv_fd((*cmd)->tokens[1], fd[1], envp);
	return ;
}
