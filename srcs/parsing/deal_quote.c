/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:32:33 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/04 18:20:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_char(char c, char *tokens, int *j, int len)
{
	int			i;
	static char	list[9] = "abntrvf\\\'";
	static char	become[9] = "\a\b\n\t\r\v\f\\\'";

	i = 0;
	while (i < 9)
	{
		if (c == list[i])
		{
			tokens[*j] = become[i];
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
		return (QUOTE_NOT_FOUND - 1);
	return (len);
}

int			deal_simple_quote(char *str, char *token, int *j, int dollar)
{
	int i;
	int len;

	i = 1;
	if ((len = len_simple_quote(str + 1, dollar) + 1) == QUOTE_NOT_FOUND)
		return (QUOTE_NOT_FOUND);
	while (i < len)
	{
		if (dollar == 1 && str[i] == '\\' && str[++i])
			i += special_char(str[i], token, j, len);
		else
		{
			token[*j] = str[i];
			++(*j);
			++i;
		}
	}
	return (len + 1);
}

int			deal_double_quote(char *str, t_list **lst, int *j, char *envp[])
{
	int i;

	i = 0;
	g_quote = 1;
	while (str[++i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] != '\'')
			i += deal_dollar(str + i, lst, j, envp) - 1;
		else if (str[i] == '\\' && (str[i + 1] == '\"' ||
		str[i + 1] == '\\' || str[i + 1] == '$'))
		{
			++i;
			(*lst)->content[*j] = str[i];
			++(*j);
		}
		else if (str[i] != '\"')
		{
			(*lst)->content[*j] = str[i];
			++(*j);
		}
	}
	g_quote = 0;
	if (str[i] == '\"')
		return (i + 1);
	return (QUOTE_NOT_FOUND);
}

int			is_in_quote(char const *s, int i, int *quote)
{
	int	bs;

	bs = 0;
	--i;
	while (s[++i] == '\\')
		++bs;
	if (s[i] == '\'' || s[i] == '\"')
	{
		if (*quote == 0 && bs % 2 == 1)
			return (i);
		else if (s[i] == '\'' && i > 0 && s[i - 1] == '$' && *quote == 0)
			*quote = 3;
		else if (s[i] == '\'' && *quote == 0)
			*quote = 1;
		else if (s[i] == '\"' && *quote == 0)
			*quote = 2;
		else if (*quote == 1 && s[i] == '\'')
			*quote = 0;
		else if (*quote == 2 && s[i] == '\"' && bs % 2 == 0)
			*quote = 0;
		else if (*quote == 3 && s[i] == '\'' && bs % 2 == 0)
			*quote = 0;
	}
	return (i);
}
