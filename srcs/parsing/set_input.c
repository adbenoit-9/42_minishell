/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/25 13:51:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		deal_space(char *str, char *input, int *j)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
	{
		input[*j] = ' ';
		++(*j);
	}
	return (i);
}

int		set_input(char *str, t_stock **cmd_lst, char *envp[])
{
	int	i;
	int j;

	i = -1;
	j = 0;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += deal_space(str + i + 1, (*cmd_lst)->input, &j);
		else if (str[i] == '\\')
		{
			(*cmd_lst)->input[j] = str[++i];
			++j;
		}
		else if (str[i] == '\'')
			i += deal_simple_quote(str + i + 1, cmd_lst, &j, 0);
		else if (str[i] == '\"')
			i += deal_double_quote(str + i + 1, cmd_lst, &j, envp);
		else if (str[i] == '$')
			i += deal_dollar(str + i + 1, cmd_lst, &j, envp);
		else if (ft_issep(str[i], 0))
		{
			i += set_sep(str + i, cmd_lst);
			break ;
		}
		else
			(*cmd_lst)->input[j++] = str[i];
	}
	(*cmd_lst)->input[j] = 0;
	return (i);
}
