/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/15 16:14:49 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var(char *var, char **input, int j, char *envp[])
{
	int		i;
	size_t	k;
	size_t	len;

	if ((i = find_var(envp, var)) == -1)
		return (j);
	k = ft_strlen(var);
	len = ft_strlen(envp[i]);
	if (len > k)
		*input = ft_realloc(*input, ft_strlen(*input) + len - k + 1);
	while (envp[i][++k])
	{
		(*input)[j] = envp[i][k];
		++j;
	}
	return (j);
}

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
	var = ft_strncpy(var, str, i);
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
