/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:32:33 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/02 23:58:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_char(char *str, char **input, int *j, int len)
{
	int i;

	i = 0;
    if (str[i] == '\\' && str[i + 1])
	{
		++i;
        if (str[i] == 'n')
        	(*input)[*j] = '\n';
        else if (str[i] == 't')
        	(*input)[*j] = '\t';
        else if (str[i] == 'r')
        	(*input)[*j] = '\r';
        else if (str[i] == 'v')
        	(*input)[*j] = '\v';
        else if (str[i] == 'f')
        	(*input)[*j] = '\f';
        else if (str[i] == 'a')
        	(*input)[*j] = '\a';
        else if (str[i] == 'b')
        	(*input)[*j] = '\b';
        else if (str[i] == '\'')
        	(*input)[*j] = '\'';
        else if (str[i] == '\"')
        	(*input)[*j] = '\"';
        else if (str[i] == '\\')
        	(*input)[*j] = '\\';
        else if (str[i] == '\'')
        	(*input)[*j] = '\'';
        else if (str[i] == '0')
        {
        	i = len;
        	--(*j);
        }
	}
	else
    	(*input)[*j] = str[i];
     ++(*j);
    return (i);
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
    return (len);
}

static int	parse_simple_quote(char *str, char **input, int *j, int dollar)
{
	int i;
    int len;

	i = 0;
    len = len_simple_quote(str, dollar);
	while (i < len)
	{
	    if (dollar == 1)
            i += special_char(str + i, input, j, i);
		else
		{
			(*input)[*j] = str[i];
			++(*j);
		}
		++i;
	}
	return (len + 1);
}

static int	parse_double_quote(char *str, char **input, int *j)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\"')
	{
		i += deal_dollar(str + i, input, j);
		if (str[i] == '\\' && str[i + 1] == '\"')
		{
			i += 2;
			(*input)[*j] = '\"';
			++(*j);
		}
		if (str[i] != '\"')
		{
			(*input)[*j] = str[i];
			++(*j);
			++i;
		}
	}
	return (i + 1);
}

int			deal_quote(char *str, char **input, int *j, int dollar)
{
	int		i;

	i = 0;
    if (str[i] == '\'')
	{
		++i;
		i += parse_simple_quote(str + i, input, j, dollar);
	}
	else if (str[i] == '\"')
	{
		++i;
		i += parse_double_quote(str + i, input, j);
	}
	return (i);
}
