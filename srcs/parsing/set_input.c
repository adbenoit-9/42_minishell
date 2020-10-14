/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/14 17:23:22 by adbenoit         ###   ########.fr       */
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
			if (input[i][j] == '\\' && input[i][++j])
				arg[k++] = input[i][j++];
			else if (input[i][j] == '\'')
				ret = deal_simple_quote(input[i] + j, &arg, &k, 0);
			else if (input[i][j] == '\"')
				ret = deal_double_quote(input[i] + j, &arg, &k, envp);
			else if (input[i][j] == '$')
				ret = deal_dollar(input[i] + j, &arg, &k, envp);
			else if (ft_issep(input[i][j], 0))
			{
				set_sep(input[i] + j, cmd_lst);
				replace_input(&arg, &input[i], k);
				input[i + 1] = NULL;
				return (1);
			}
			else
			{
				arg[k] = input[i][j];
				++k;
				++j;
			}
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
			printf("ret = %d, j =%d\n", ret, j);
		}
		printf("-----\n");
		replace_input(&arg, &input[i], k);
		++i;
	}
	// input[i] = NULL;
	return (0);
}