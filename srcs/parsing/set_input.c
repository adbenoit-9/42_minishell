/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 15:44:13 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		deal_space(char *str, char **arg, int *k)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	if (str[i])
// 	{
// 		*arg[*k] = ' ';
// 		++(*k);
// 	}
// 	return (i);
// }

// int		set_input(char *str, t_stock **cmd_lst, char *envp[])
// {
// 	int	i;
// 	int j;

// 	i = -1;
// 	j = 0;
// 	while (str[++i] && str[i] != '\n')
// 	{
// 		if (str[i] == ' ' || str[i] == '\t')
// 			i += deal_space(str + i + 1, (*cmd_lst)->input, &j);
// 		else if (str[i] == '\\')
// 		{
// 			(*cmd_lst)->input[j] = str[++i];
// 			++j;
// 		}
// 		else if (str[i] == '\'')
// 			i += deal_simple_quote(str + i + 1, cmd_lst, &j, 0);
// 		else if (str[i] == '\"')
// 			i += deal_double_quote(str + i + 1, cmd_lst, &j, envp);
// 		else if (str[i] == '$')
// 			i += deal_dollar(str + i + 1, cmd_lst, &j, envp);
// 		else if (ft_issep(str[i], 0))
// 		{
// 			i += set_sep(str + i, cmd_lst);
// 			break ;
// 		}
// 		else
// 			(*cmd_lst)->input[j++] = str[i];
// 	}
// 	(*cmd_lst)->input[j] = 0;
// 	return (i);
// }

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
					return (-1);	
				else
					j += len;
			}
			else if (input[i][j] == '$')
				j += deal_dollar(input[i] + j, &arg, &k, envp);
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