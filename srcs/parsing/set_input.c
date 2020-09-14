/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 18:00:11 by adbenoit         ###   ########.fr       */
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

void	set_input(char *str, char **input, char *envp[])
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
			i += deal_double_quote(str + i + 1, input, &j, envp);
		else if (str[i] == '$')
			i += deal_dollar(str + i + 1, input, &j, envp);
		else
			(*input)[j++] = str[i];
	}
	(*input)[j] = 0;
}
