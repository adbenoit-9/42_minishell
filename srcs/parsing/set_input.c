/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 19:09:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_input(char **input, t_stock **cmd_lst, char **envp)
{
	int i;
	int j;
	int k;
	int	len;
	char *arg;

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
			if (input[i][j] == '\\')
			{
				arg[k++] = input[i][++j];
				++j;
			}
			else if (input[i][j] == '\'' || input[i][j] == '\"')
			{
				if (input[i][j] == '\'')
					len = deal_simple_quote(input[i] + j, &arg, &k, 0);
				else
					len = deal_double_quote(input[i] + j, &arg, &k, envp);
				if (len == -1)
				{
					write_error("", "", "missing a quote\n");
					return (-1);
				}
				else
					j += len;
			}
			else if (input[i][j] == '$')
			{
				if ((len = deal_dollar(input[i] + j, &arg, &k, envp)) == -1)
				{
					write_error("", "", "missing a quote\n");
					return (-1);
				}
				j += len;
			}
			else if (ft_issep(input[i][j], 0))
			{
				i += set_sep(input[i] + j, cmd_lst);
				arg[k] = 0;
				free(input[i]);
				input[i] = NULL;
				input[i] = ft_strdup(arg);
				free(arg);
				arg = NULL;
				input[i + 1] = NULL;
				return (1);
			}
			else
			{
				arg[k] = input[i][j];
				++k;
				++j;
			}
		}
		arg[k] = 0;
		free(input[i]);
		input[i] = NULL;
		input[i] = ft_strdup(arg);
		free(arg);
		arg = NULL;
		++i;
	}
	return (0);
}