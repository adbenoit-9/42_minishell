/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 17:08:02 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var(char *var, char **input, int k, char *envp[])
{
	int		i;
	int		j;
	size_t	size;
	size_t	size_var;

	i = 0;
	size = ft_strlen(var);
	size_var = 0;
	if ((i = find_var(envp, var)) == -1)
		return (k);
	j = 0;
	while (envp[i][++j])
		++size_var;
	if (size_var > size)
		*input = ft_realloc(*input, ft_strlen(*input) + size_var - size + 1);
	j = size;
	if (envp[i])
	{
		while (envp[i][++j])
		{
			(*input)[k] = envp[i][j];
			++k;
		}
	}
	return (k);
}

static int	deal_var(char *str, char **input, int *j, char *envp[])
{
	char	*var;
	int		size;
	int		i;
	int		k;

	i = 0;
	size = 0;
	while ((str[size] > 47 && str[size] < 58) || (str[size] > 64 &&
	str[size] < 89) || (str[size] > 96 && str[size] < 123))
		++size;
	if (!(var = malloc(size + 1)))
		return (ft_error(NULL));
	k = -1;
	while (++k < size)
	{
		var[k] = str[i];
		++i;
	}
	var[k] = 0;
	*j = get_var(var, input, *j, envp);
	// printf("i = %d, str = %s | %p, c = \"%c\"\n", i, str, &str, str[i]);
	// printf("var = %s, %p\n", var, &var);
	// free(var);
	// var = NULL;
	// printf("var = %s, %p\n", var, &var);
	// printf("i = %d, str = %s | %p, c = \"%c\"\n", i, str, str, str[i]);
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
