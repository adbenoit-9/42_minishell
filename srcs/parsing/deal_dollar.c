/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 19:29:39 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_var(char *str, char **input, int *j, char *envp[])
{
	char	*var;
	int		i;
	int		k;

	i = 0;
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
		++i;
	if (!(var = malloc(i + 1)))
		return (-1);
	ft_strncpy(var, str, i);
	var[i] = 0;
	k = *j;
	(*input) = replace_var_by_value(var, envp, (*input), j);
	if (k == *j)
	{
		while (str[i] == ' ' || str[i] == '\t')
			++i;
	}
	free(var);
	var = NULL;
	return (i);
}

int			deal_dollar(char *str, char **input, int *j, char *envp[])
{
	int	i;

	i = 1;
	if (ft_isalnum(str[i]) == 1)
		i += deal_var(str + i, input, j, envp);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i, input, j, 1);
	else if (str[i] == '\"')
		i += deal_double_quote(str + i, input, j, envp);
	else if (str[i] == '{')
	{
		i += deal_var(str + i + 1, input, j, envp) + 1;
		if (str[i] == '}')
			++i;
		else
			return (-1);
	}
	else
	{
		(*input)[*j] = str[i - 1];
		(*input)[*j + 1] = str[i];
		++i;
		*j += 2;
	}
	if (i == 0)
		return (-1);
	return (i);
}
