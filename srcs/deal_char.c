/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/02 16:59:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_char(char *str, char **input, int *j)
{
	int	i;

	i = 1;
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
	else if (str[i] == '0')
		;
	else
		return (i);
	++(*j);
	return (i + 1);
}

static int		deal_var(char *str)
{
	char	*var;
	int		size;
	int		i;
	int		k;
	
	i = 1;
	size = 0;
	while (str[i + size] && str[i + size] != '\'' && str[i + size] != '\"' && str[i + size] != '$' && str[i + size] != ' ')
		++size;
	if (!(var = malloc(size + 1)))
		return (ft_error(NULL));
	k = -1;
	while (++k < size)
	{
		var[k] = str[i];
		i++;
	}
	var[k] = 0;
	// rechercher la variable dans env et mettre sa valeur dans input
	// find_var(var, input, j);
	// en attendant elle n'existe pas pour moi
	free(var);
	return (i);
}

int			deal_dollar(char *str, char **input, int *j)
{
	int 	i;

	i = 0;
	if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != ' ' && str[i + 1] != '\\' && str[i + 1] != '\'' && str[i + 1] != '\"')
		return (deal_var(str + i));
	else if (str[i] == '$' && str[i + 1] == '\'')
		return (deal_quote(str + i + 1, input, j, 1));
	else if (str[i] == '$' && str[i + 1] == '\"')
		return (deal_quote(str + i + 1, input, j, 0));
	else if (str[i] == '$')
	{
		(*input)[*j] = str[i];
		++i;
		++(*j);
	}
	return (i);
}

int			deal_quote(char *str, char **input, int *j, int dollar)
{
	char	quote;
	int		i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
		{
			if (quote == '\"')
				i += deal_dollar(str + i, input, j);
			else if (quote == '\'' && dollar == 1 && str[i] == '\\')
				i += special_char(str + i, input, j);
			(*input)[*j] = str[i];
			++(*j);
			++i;
		}
		return (i);
	}
	return (i);
}

int			deal_backslash(char *str, char **input, int *j)
{
	int i;

	i = 0;
	if (str[i] == '\\' && str[++i])
	{
		(*input)[*j] = str[i];
		++(*j);
		return (i + 1);
	}
	return (i);
}
