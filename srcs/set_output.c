/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:37:39 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/25 18:56:17 by adbenoit         ###   ########.fr       */
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

int		deal_quote(char *input, char **output, int i, int *j)
{
	char	quote;

	if (input[i] == '\'' || input[i] == '\"')
	{
		quote = input[i];
		i++;
		while (input[i] != quote)
		{
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
		if (input[i] != ' ' && input[i] != '\\' && input[i] != '\'' && input[i] != '\"')
		{
			(*output)[j] = input[i];
			++i;
			++j;
		}
	}
	(*output)[j] = 0;
}
