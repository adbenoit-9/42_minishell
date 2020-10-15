/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/15 14:31:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_input(char **arg, char **input, int k)
{
	(*arg)[k] = 0;
	free(*input);
	*input = NULL;
	*input = ft_strdup(*arg);
	free(*arg);
	*arg = NULL;
}

int			set_input(char **input, t_stock **cmd_lst, char **envp)
{
	int		i;
	int		j;
	int		k;
	int		ret;
	char	*arg;

	i = 0;
	arg = NULL;
	while (input[i])
	{
		k = 0;
		if (!(arg = malloc(ft_strlen(input[i]) + 1)))
			return (-1);
		j = 0;
		while (input[i][j])
		{
			ret = 0;
			if (input[i][j] == '\\' && input[i][++j])
				arg[k++] = input[i][j++];
			else if (input[i][j] == '\'')
				ret = deal_simple_quote(input[i] + j, &arg, &k, 0);
			else if (input[i][j] == '\"')
				ret = deal_double_quote(input[i] + j, &arg, &k, envp);
			else if (input[i][j] == '$')
				ret = deal_dollar(input[i] + j, &arg, &k, envp);
			else
				arg[k++] = input[i][j++];
			if (ret == QUOTE_NOT_FOUND)
				return (QUOTE_NOT_FOUND);
			else if (ret == VAR_NOT_FOUND)
			{
				(*cmd_lst)->err = VAR_NOT_FOUND;
				arg[k] = 0;
				break ;
			}
			else
				j += ret;
		}
		replace_input(&arg, &input[i], k);
		++i;
	}
	return (0);
}
