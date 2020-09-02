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

	i = 0;
	if (str[i] == ' ')
	{
		(*input)[*j] = ' ';
		i++;
		++(*j);

	}
	while (str[i] == ' ')
		i++;
	return (i);
}

void	find_var(char *var, char **input, int *j)
{
	(void)var;
	(void)input;
	(void)j;
}


void 	set_input(char *str, char **input)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		i += deal_space(str + i, input, &j);
		i += deal_backslash(str + i, input, &j);
		i += deal_quote(str + i, input, &j, 0);
		i += deal_dollar(str + i, input, &j);
		if (str[i] != ' ' && str[i] != '\\' && str[i] != '\''
		&& str[i] != '\"' && str[i] != '$')
		{
			(*input)[j] = str[i];
			++i;
			++j;
		}
	}
	if (j != 0)
		(*input)[j - 1] = 0;
	(*input)[j] = 0;
}
