/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/15 20:57:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_var(char *str, char **input, int *j, char *envp[])
{
	char	*var;
	int		i;

	i = 0;
	while ((str[i] > 47 && str[i] < 58) || (str[i] > 64 &&
	str[i] < 89) || (str[i] > 96 && str[i] < 123))
		++i;
	if (!(var = malloc(i + 1)))
		return (ft_error(NULL));
	ft_strncpy(var, str, i);
	var[i] = 0;
	*input = replace_var_by_value(var, envp, *input, j);
	free(var);
	var = NULL;
	return (i);
}

int			deal_dollar(char *str, char **input, int *j, char *envp[])
{
	int	i;

	i = 0;
	if (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\\'
	&& str[i] != '\'' && str[i] != '\"')
		i += deal_var(str + i, input, j, envp);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i + 1, input, j, 1) + 1;
	else if (str[i] == '\"')
		i += deal_double_quote(str + i + 1, input, j, envp) + 1;
	else
	{
		(*input)[*j] = str[i];
		++i;
		++(*j);
	}
	return (i);
}
