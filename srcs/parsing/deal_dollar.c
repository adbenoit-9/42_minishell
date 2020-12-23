/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 15:08:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_var_by_value(char *name, char **value, int *start, char *envp[])
{
	int	i;
	int	k;
	int	len;

	i = 0;
	if (!ft_getenv(name, &i, envp))
		return (VAR_NOT_FOUND);
	k = ft_strlen(name);
	len = ft_strlen(envp[i]);
	if (len != k)
	{
		if (!(*value = ft_realloc(*value, len - k + ft_strlen(*value) + 1)))
			return (MALL_ERR);
	}
	while (ft_strcmp(envp[i] + k, "=") != 0 && envp[i][k] && envp[i][++k])
	{
		(*value)[*start] = envp[i][k];
		++(*start);
	}
	(*value)[*start] = 0;
	return (0);
}

static int	deal_var(char *str, char **token, int *j, char *envp[])
{
	char	*name;
	int		i;
	int		k;

	i = 0;
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
		++i;
	if (!(name = malloc(i + 1)))
		return (MALL_ERR);
	ft_strncpy(name, str, i);
	name[i] = 0;
	k = replace_var_by_value(name, token, j, envp);
	free(name);
	name = NULL;
	if (k == VAR_NOT_FOUND && *j == 0 && !str[i])
		return (VAR_NOT_FOUND);
	else if (k == MALL_ERR)
		return (k);
	return (i);
}

int			deal_status(char **new_token, int *k, int size)
{
	char	*nb;
	int		len;

	nb = ft_itoa(g_status);
	if ((len = ft_strlen(nb)) > 2)
	{
		if (!(*new_token = ft_realloc(*new_token, size + len)))
			return (MALL_ERR);
	}
	ft_strcpy(*new_token + *k, nb);
	(*k) += len;
	free(nb);
	return (2);
}

int			deal_dollar(char *str, char **tokens, int *j, char *envp[])
{
	int	i;
	int ret;

	i = 1;
	if (ft_isalnum(str[i]) == 1 || str[i] == '_')
		i += deal_var(str + i, tokens, j, envp);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i, tokens, j, 1);
	else if (str[i] == '\"' && str[i + 1])
		i += deal_double_quote(str + i, tokens, j, envp);
	else if (str[i] == '{')
	{
		ret = deal_var(str + i + 1, tokens, j, envp) + 1;
		if (ret < 0)
			return (ret);
		i += ret;
		if (str[i] != '}')
			return (QUOTE_NOT_FOUND);
		++i;
	}
	else
		(*tokens)[(*j)++] = '$';
	if (i <= 0)
		return (i - 1);
	return (i);
}
