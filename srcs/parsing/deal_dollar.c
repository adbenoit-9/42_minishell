/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:16:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/17 14:09:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_var(char *str, t_stock **cmd_lst, int *j, char *envp[])
{
	char	*var;
	int		i;

	i = 0;
	while ((str[i] > 47 && str[i] < 58) || (str[i] > 64 &&
	str[i] < 89) || (str[i] > 96 && str[i] < 123))
		++i;
	if (!(var = malloc(i + 1)))
		return (ft_error(cmd_lst));
	ft_strncpy(var, str, i);
	var[i] = 0;
	(*cmd_lst)->input = replace_var_by_value(var, envp, (*cmd_lst)->input, j);
	free(var);
	var = NULL;
	return (i);
}

int			deal_dollar(char *str, t_stock **cmd_lst, int *j, char *envp[])
{
	int	i;

	i = 0;
	if (ft_isalnum(str[i]) == 1)
		i += deal_var(str + i, cmd_lst, j, envp);
	else if (str[i] == '\'')
		i += deal_simple_quote(str + i + 1, cmd_lst, j, 1) + 1;
	else if (str[i] == '\"')
		i += deal_double_quote(str + i + 1, cmd_lst, j, envp) + 1;
	else if (str[i] == '{')
	{
		i += deal_var(str + i + 1, cmd_lst, j, envp) + 1;
		if (str[i] == '}')
			++i;
		else
			(*cmd_lst)->err = 1;
	}
	else
	{
		(*cmd_lst)->input[*j] = str[i - 1];
		(*cmd_lst)->input[*j + 1] = str[i];
		++i;
		*j += 2;
	}
	return (i);
}
