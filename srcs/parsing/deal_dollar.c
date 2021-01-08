/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 13:58:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cutenv(char *value, t_list **lst, int *j, char *str)
{
	int		i;
	t_list	*new;
	char	**token;

	if (!value)
		return (0);
	if (!(token = ft_split(value, ' ')))
		return (MALL_ERR);
	i = -1;
	while (token[++i])
	{
		*j = ft_strlen(token[i]);
		new = (token[i + 1]) ? ft_lstnew(ft_strdup(token[i])) :
		ft_lstnew(ft_strjoin(token[i], str));
		if (!new)
		{
			ft_freetab(token);
			return (MALL_ERR);
		}
		ft_lstadd_back(lst, new);
	}
	ft_freetab(token);
	return (0);
}

static int	replace_var_by_value(char *value, t_list **lst, int *j, char *str)
{
	int		i;
	int		len;

	i = 0;
	if (!value || !value[0])
		return (VAR_NOT_FOUND);
	len = ft_strlen(value) + ft_strlen(str) + *j + 1;
	if (!((*lst)->content = ft_realloc((*lst)->content, len)))
		return (MALL_ERR);
	while (g_quote == 0 && value[i] == ' ')
		++i;
	while (value[i] && value[i] != ' ')
	{
		(*lst)->content[*j] = value[i];
		++(*j);
		++i;
	}
	(*lst)->content[(*j)] = 0;
	if (g_quote == 0)
		return (ft_cutenv(value + i, lst, j, str));
	ft_strcat((*lst)->content, value + i);
	*j = ft_strlen((*lst)->content);
	return (0);
}

static int	deal_var(char *str, t_list **lst, int *j, char *envp[])
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
	k = replace_var_by_value(ft_getenv(name, 0, envp), lst, j, str + i);
	free(name);
	name = NULL;
	if (k == VAR_NOT_FOUND && *j == 0 && !str[i])
		return (VAR_NOT_FOUND);
	else if (k == MALL_ERR)
		return (k);
	return (i);
}

int			deal_status(char **token, int *k, int size)
{
	char	*nb;
	int		len;

	nb = ft_itoa(g_status);
	if ((len = ft_strlen(nb)) > 2)
	{
		if (!(*token = ft_realloc(*token, size + len)))
		{
			free(nb);
			return (MALL_ERR);
		}
	}
	ft_strcpy(*token + *k, nb);
	(*k) += len;
	free(nb);
	return (2);
}

int			deal_dollar(char *str, t_list **lst, int *j, char *envp[])
{
	int	i;
	int ret;

	i = 1;
	if (ft_isalnum(str[i]) == 1 || str[i] == '_')
		i += deal_var(str + i, lst, j, envp);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i, (*lst)->content, j, 1);
	else if (str[i] == '\"' && str[i + 1])
		i += deal_double_quote(str + i, lst, j, envp);
	else if (str[i] == '{')
	{
		ret = deal_var(str + i + 1, lst, j, envp) + 1;
		if (ret < 0)
			return (ret);
		i += ret;
		if (str[i] != '}')
			return (QUOTE_NOT_FOUND);
		++i;
	}
	else
		(*lst)->content[(*j)++] = '$';
	if (i <= 0)
		return (i - 1);
	return (i);
}
