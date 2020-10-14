/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:32:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/14 16:41:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_char(char c, char **input, int *j, int len)
{
	int			i;
	static char	list[9] = "abntrvf\\\'";
	static char	become[9] = "\a\b\n\t\r\v\f\\\'";

	i = 0;
	while (i < 9)
	{
		if (c == list[i])
		{
			(*input)[*j] = become[i];
			++(*j);
			return (1);
		}
		++i;
	}
	if (c == '0')
		return (len);
	return (0);
}

static int	len_simple_quote(char *str, int dollar)
{
	int len;

	len = 0;
	while (str[len] && str[len] != '\'')
	{
		if (dollar == 1 && str[len] == '\\' && str[len + 1])
			len += 2;
		else
			++len;
	}
	if (str[len] != '\'')
		return (QUOTE_NOT_FOUND);
	return (len);
}

int			deal_simple_quote(char *str, char **input, int *j, int dollar)
{
	int i;
	int len;

	i = 1;
	if ((len = len_simple_quote(str + 1, dollar) + 1) == 0)
		return (-1);
	while (i < len)
	{
		if (dollar == 1 && str[i] == '\\' && str[++i])
			i += special_char(str[i], input, j, len);
		else
		{
			(*input)[*j] = str[i];
			++(*j);
			++i;
		}
	}
	return (len + 1);
}

int			deal_double_quote(char *str, char **input, int *j, char *env[])
{
	int i;

	i = 0;
	while (str[++i] && str[i] != '\"')
	{
		if (str[i] == '$')
			i += deal_dollar(str + i, input, j, env) - 1;
		else if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
		{
			++i;
			(*input)[*j] = str[i];
			++(*j);
		}
		else if (str[i] != '\"')
		{
			(*input)[*j] = str[i];
			++(*j);
		}
	}
	if (str[i] == '\"')
		return (i + 1);
	return (QUOTE_NOT_FOUND);
}

int			is_in_quote(char const *s, size_t *i, int quote)
{
	int	bs;

	bs = 0;
	--(*i);
	while (s[++(*i)] == '\\')
		++bs;
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		if (quote == 0 && bs % 2 == 1)
			return (quote);
		else if (s[*i] == '\'' && i > 0 && s[*i - 1] == '$' && quote == 0)
			return (3);
		else if (s[*i] == '\'' && quote == 0)
			return (1);
		else if (s[*i] == '\"' && quote == 0)
			return (2);
		else if (quote == 1 && s[*i] == '\'')
			return (0);
		else if (quote == 2 && s[*i] == '\"' && bs % 2 == 0)
			return (0);
		else if (quote == 3 && s[*i] == '\'' && bs % 2 == 0)
			return (0);
	}
	return (quote);
}
