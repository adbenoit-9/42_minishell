/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:37:39 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/29 16:03:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		deal_space(char *input, char **output, int i, int *j)
{
	if (input[i] == ' ')
	{
		(*output)[*j] = ' ';
		i++;
		++(*j);

	}
	while (input[i] == ' ')
		i++;
	return (i);
}

void	find_var(char *var, char **output, int *j)
{
	(void)var;
	(void)output;
	(void)j;
}

int		deal_dollar(char *input, char **output, int i, int *j)
{
	char	*var;
	int		k;
	int		size;

	size = 0;
	if (input[i] == '$' && input[i + 1] && input[i + 1] != '$' && input[i + 1] != ' ' && input[i + 1] != '\\')
	{
		++i;
		while (input[i + size] && input[i + size] != '\'' && input[i + size] != '\"' && input[i + size] != '$' && input[i + size] != ' ')
			++size;
		if (!(var = malloc(size + 1)))
			return (ft_error(NULL));
		k = -1;
		while (++k < size)
		{
			var[k] = input[i];
			i++;
		}
		var[k] = 0;
		// rechercher la variable dans env et mettre sa valeur dans output
		// find_var(var, output, j);
		// en attendant elle n'existe pas pour moi
		free(var);
		return (i);
	}
	else if (input[i] == '$')
	{
		(*output)[*j] = input[i];
		++i;
		++(*j);
	}
	return (i);
}

int		deal_quote(char *input, char **output, int i, int *j)
{
	char	quote;

	if (input[i] == '\'' || input[i] == '\"')
	{
		quote = input[i];
		i++;
		while (input[i] && input[i] != quote)
		{
			if (quote == '\"')
				deal_dollar(input, output,i, j);
			(*output)[*j] = input[i];
			++(*j);
			++i;
		}
		return (i + 1);
	}
	return (i);
}

int		deal_backslash(char *input, char **output, int i, int *j)
{
	if (input[i] == '\\' && input[++i])
	{
		(*output)[*j] = input[i];
		++(*j);
		return (i + 1);
	}
	return (i);
}

void 	set_output(char *input, char **output)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		i = deal_space(input, output, i, &j);
		i = deal_backslash(input, output, i, &j);
		i = deal_quote(input, output, i, &j);
		i = deal_dollar(input, output,i, &j);
		if (input[i] != ' ' && input[i] != '\\' && input[i] != '\''
		&& input[i] != '\"' && input[i] != '$')
		{
			(*output)[j] = input[i];
			++i;
			++j;
		}
	}
	(*output)[j] = 0;
}
