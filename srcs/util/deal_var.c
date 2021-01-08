/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 01:04:20 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 14:04:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_name(char *var)
{
	int i;

	if (!var)
		return (1);
	if (!var[0])
		return (0);
	if (var[0] && ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

int	find_var(char *envp[], char *var)
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
	return (VAR_NOT_FOUND);
}

int	replace_var_by_value(char *var, char *envp[], char **value, int *start)
{
	int	i;
	int	k;
	int	len;

	if ((i = find_var(envp, var)) == VAR_NOT_FOUND)
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
