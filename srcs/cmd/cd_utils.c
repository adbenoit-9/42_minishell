/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/16 21:06:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	path_len(char *token)
{
	size_t	i;
	size_t	len;
	size_t	tmp;

	len = 0;
	i = 0;
	while (token && token[i])
	{
		++len;
		tmp = i;
		while (token[tmp] == '/' && token[i + 1] == '/')
			++i;
		++i;
	}
	return (len);
}

int		modify_pwd(char *str, char *envp[], char *var)
{
	int		i;
	int		j;
	int		k;
	size_t	size;

	size = 0;
	if (!str)
		str = getcwd(NULL, size);
	i = find_var(envp, var);
	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		++j;
	size += ft_strlen(var) + 1;
	if (ft_strlen(envp[i]) < size && !(envp[i] = realloc(envp[i], size + 1)))
		return (print_errno("cd", NULL, MALL_ERR));
	k = -1;
	while (str && str[++k])
		envp[i][++j] = str[k];
	envp[i][j + 1] = 0;
	return (0);
}

int		without_arg(t_stock **cmd, char **envp)
{
	int	pos;

	if ((pos = find_var(envp, "HOME")) == -1)
	{
		print_error("cd : ", "HOME not set\n", NULL, 1);
		return (-1);
	}
	if (!((*cmd)->tokens = ft_realloc_tab((*cmd)->tokens, 2)))
		return (print_errno(NULL, strerror(errno), MALL_ERR));
	(*cmd)->tokens[1] = ft_strdup(envp[pos] + 5);
	return (0);
}

char	*correct_path(char *arg)
{
	int		i;
	int		j;
	int		tmp;
	char	*path;

	if (ft_strcmp(arg, "//tmp") == 0)
		return (arg);
	if (!(path = malloc(path_len(arg) + 1)))
	{
		print_errno(NULL, strerror(errno), MALL_ERR);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (arg[++i])
	{
		path[j++] = arg[i];
		tmp = i;
		while (arg[tmp] == '/' && arg[i + 1] == '/')
			++i;
	}
	path[j] = 0;
	return (path);
}

int		check_tmp(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '/')
	{
		count++;
		i++;
		while (str[i] == '/')
		{
			i++;
			count++;
		}
	}
	if (str[i] != 't' || str[i + 1] != 'm' || str[i + 2] != 'p')
		return (0);
	if (count == 2)
		return (2);
	else
		return (1);
}
