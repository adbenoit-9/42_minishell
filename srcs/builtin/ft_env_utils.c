/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 01:04:20 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/29 17:58:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_replace_by_env(char *var, char **value, int *start, char *envp[])
{
	int	i;
	int	k;
	int	len;

	if (!ft_getenv(var, &i, envp))
		return (VAR_NOT_FOUND);
	k = ft_strlen(var);
	len = ft_strlen(envp[i]);
	if (ft_strcmp(envp[i] + k, "=\'\'") == 0)
		len -= 3;
	if (len != k)
	{
		if (!(*value = ft_realloc(*value, len - k + ft_strlen(*value) + 1)))
			return (errno_msg(NULL, NULL, MALL_ERR));
	}
	while (ft_strcmp(envp[i] + k, "=\'\'") != 0 && envp[i][++k])
	{
		(*value)[*start] = envp[i][k];
		++(*start);
	}
	(*value)[*start] = 0;
	return (0);
}

/*
** n is the index of the variable in env
*/

char	*ft_getenv(char *name, int *n, char *envp[])
{
	int size;
	int i;

	if (!name || !name[0])
		return (NULL);
	size = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, size) == 0 &&
		(envp[i][size] == '=' || !envp[i][size]))
		{
			if (envp[i][size] == '=')
				++size;
			if (n)
				*n = i;
			return (envp[i] + size);
		}
		++i;
	}
	return (NULL);
}

/*
** str have to be malloc
*/

int			ft_putenv(char *name, char *str, char *envp[])
{
	int	n;

	if (!name || !name[0])
		return (-1);
	n = 0;
	if (!ft_getenv(name, &n, envp))
	{
		n = ft_tabsize(envp);
		envp[n + 1] = 0;
	}
	free(envp[n]);
	envp[n] = str;
	return (0);
}

/*
** mode can be worth 0 (= replace value) or 1 (= mode to value)
*/

int			ft_setenv(char *name, char *value, int mode, char *envp[])
{
	char	*new;
	int		size;
	int		len;
	int		n;

	if (!name || !name[0])
		return (-1);
	size = ft_tabsize(envp);
	len = ft_strlen(name) + ft_strlen(value) + 1;
	if (!ft_getenv(name, &n, envp))
		n = size;
	else if (mode == 1)
		len = ft_strlen(envp[n]) + ft_strlen(value);
	if (!(new = malloc(len + 1)))
		return (-1);
	if (mode == 0)
	{
		ft_strcpy(new, name);
		ft_strcat(new, "=");
	}
	else
		ft_strcpy(new, envp[n]);
	ft_strcat(new, value);
	return (ft_putenv(name, new, envp));
}

static int	ft_place(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (1);
		else if (s1[i] > s2[i])
			return (2);
		else
			i++;
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (1);
	if (s1[i] != '\0' && s2[i] == '\0')
		return (2);
	return (0);
}

void		ft_sort_env(char **env)
{
	char	*swap;
	int		size;
	int		i;
	int		j;

	swap = NULL;
	size = ft_tabsize(env);
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_place(env[j], env[j + 1]) == 2)
			{
				swap = env[j];
				env[j] = env[j + 1];
				env[j + 1] = swap;
			}
		}
	}
	return ;
}
