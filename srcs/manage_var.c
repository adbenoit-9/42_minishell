/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:46:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/15 16:32:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_var(char *envp[], char *var)
{
	int	i;
	int size;

	size = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, size) == 0 && envp[i][size] == '=')
			return (i);
		++i;
	}
	return (-1);
}

char	*replace_var_by_value(char *var, char *envp[], char *value, int *start)
{
	int		i;
	size_t	k;
	size_t	len;

	if ((i = find_var(envp, var)) == -1)
		return (value);
	k = ft_strlen(var);
	len = ft_strlen(envp[i]);
	if (len > k)
		value = ft_realloc(value, ft_strlen(value) + len - k + 1);
	while (envp[i][++k])
	{
		value[*start] = envp[i][k];
		++(*start);
	}
	return (value);
}
