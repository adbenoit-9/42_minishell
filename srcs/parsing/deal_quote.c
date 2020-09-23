/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:32:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/23 18:35:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_char(char c, t_stock **cmd_lst, int *j, int len)
{
	int			i;
	static char	list[9] = "abntrvf\\\'";
	static char	become[9] = "\a\b\n\t\r\v\f\\\'";

	i = 0;
	while (i < 9)
	{
		if (c == list[i])
		{
			(*cmd_lst)->input[*j] = become[i];
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
			++len;
		++len;
	}
	return (len);
}

int			deal_simple_quote(char *str, t_stock **cmd_lst, int *j, int dollar)
{
	int i;
	int len;

	i = 0;
	len = len_simple_quote(str, dollar);
	while (i < len)
	{
		if (dollar == 1 && str[i] == '\\' && str[++i])
			i += special_char(str[i], cmd_lst, j, len);
		else
		{
			(*cmd_lst)->input[*j] = str[i];
			++(*j);
			++i;
		}
	}
	if (str[len] == '\'')
		return (len + 1);
	(*cmd_lst)->err = 1;
	return (len);
}

int			deal_double_quote(char *str, t_stock **cmd_lst, int *j, char *env[])
{
	int i;

	i = -1;
	while (str[++i] && str[i] != '\"')
	{
		if (str[i] == '$')
			i += deal_dollar(str + i + 1, cmd_lst, j, env);
		else if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
		{
			++i;
			(*cmd_lst)->input[*j] = str[i];
			++(*j);
		}
		else if (str[i] != '\"')
		{
			(*cmd_lst)->input[*j] = str[i];
			++(*j);
		}
	}
	if (str[i] == '\"')
		return (i + 1);
	(*cmd_lst)->err = 1;
	return (i);
}
