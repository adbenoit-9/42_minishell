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

static size_t	path_len(char *token)
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

static int		modify_pwd(char *str, char *envp[], char *var)
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
	free(str);
	return (0);
}

static int		without_arg(t_stock **cmd, char **envp)
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

static char		*correct_path(char *arg)
{
	int		i;
	int		j;
	int		tmp;
	char	*path;

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

void			ft_cd(t_stock **cmd, char *envp[], int *fd)
{
	char	*str;
	char	*path;

	(void)fd;
	if (!(*cmd)->tokens[1] && without_arg(cmd, envp) < 0)
		return ;
	if (!(path = correct_path((*cmd)->tokens[1])))
		return ;
	str = getcwd(NULL, 0);
	chdir((const char *)path);
	free(path);
	if (errno == 0)
	{
		modify_pwd(str, envp, "OLDPWD");
		modify_pwd(NULL, envp, "PWD");
	}
	if (errno != 0)
		print_errno("cd", (*cmd)->tokens[1], 0);
}
