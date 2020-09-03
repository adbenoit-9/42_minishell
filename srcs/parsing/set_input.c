/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:37:39 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/02 16:51:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		deal_space(char *str, char **input, int *j)
{
	int i;

	(*input)[*j] = ' ';
	++(*j);
	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void 	set_input(char *str, char **input)
{
	int	i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ')
			i += deal_space(str + i + 1, input, &j);
		else if (str[i] == '\\')
		{
			(*input)[j] = str[++i];
			++j;
		}
		else if (str[i] == '\'')
			i += deal_simple_quote(str + i + 1, input, &j, 0);
		else if (str[i] == '\"')
			i += deal_double_quote(str + i + 1, input, &j);
		else if (str[i] == '$')
			i += deal_dollar(str + i + 1, input, &j);
		else
			(*input)[j++] = str[i];
	}
	(*input)[j] = 0;
}
