/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/03 00:20:12 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	find_var(char *var, char **input, int *j)
// {
// }

static int		deal_var(char *str)
{
	char	*var;
	int		size;
	int		i;
	int		k;
	
	i = 1;
	size = 0;
	while (str[i + size] && str[i + size] != '\'' && str[i + size] != '\"'
	&& str[i + size] != '$' && str[i + size] != ' ')
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
	if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != ' '
	&& str[i + 1] != '\\' && str[i + 1] != '\'' && str[i + 1] != '\"')
		i += deal_var(str + i);
	else if (str[i] == '$' && str[i + 1] == '\'')
	{
		++i;
		i += deal_quote(str + i, input, j, 1);
	}
	else if (str[i] == '$' && str[i + 1] == '\"')
	{
		++i;
		i += deal_quote(str + i, input, j, 0);
	}
	else if (str[i] == '$')
	{
		(*input)[*j] = str[i];
		++i;
		++(*j);
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
