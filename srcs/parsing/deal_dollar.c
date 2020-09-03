/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/03 22:31:53 by adbenoit         ###   ########.fr       */
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
	
	i = 0;
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
	if (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\\'
	&& str[i] != '\'' && str[i] != '\"')
		i += deal_var(str + i);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i + 1, input, j, 1) + 1;
	else if (str[i] == '\"')
		i += deal_double_quote(str + i + 1, input, j) + 1;
	else
	{
		(*input)[*j] = str[i];
		++i;
		++(*j);
	}
	return (i);
}
