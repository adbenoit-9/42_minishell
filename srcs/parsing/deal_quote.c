/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:32:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 18:48:53 by adbenoit         ###   ########.fr       */
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
		return (-1);
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
			i += deal_dollar(str + i + 1, input, j, env);
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
	return (-1);
}
