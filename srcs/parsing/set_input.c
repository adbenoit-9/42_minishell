/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/16 14:43:15 by adbenoit         ###   ########.fr       */
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

int fill_std(char **std, char *str)
{
	size_t	i;
	int 	j;
	int 	size;
	size_t	tmp;

	i = 1;
	size = 0;
	while (str[i] == ' ')
			++i;
	if (ft_issep(str[i], 0) == 1)
		return (1);
	if (!std)
		size = 1;
	else
	{
		while (std[size])
		++size;
	}
	std = realloc_tab(std, size + 1);
	while (str[i])
	{
		tmp = i;
		j = is_in_quote(str, &tmp, j);
		i = j != 0 ? tmp : i;
		if (j == 0 && is_bs(str, &i) == 0 && ft_issep(str[i], 0) == 1)
			break ;
		++i;
	}
	std[size - 1] = malloc(i + 1);
	j = -1;
	while (++j < (int)i)
		std[size - 1][j] = str[i - j];
	std[size - 1][j] = 0;
	std[size] = 0;
	return (i);
}

int			set_std(t_stock **cmd_lst, char *str, char redirec)
{
	int i;

	i = 0;
	printf("here %s\n", str);
	if (redirec == '<')
		i = fill_std((*cmd_lst)->stdin, str);
	else
		i = fill_std((*cmd_lst)->stdout, str);
	return (i);
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
			else if (input[i][j] == '>' || input[i][j] == '<')
			{
				set_std(cmd_lst, input[++i], input[i][j]);
				break ;
			}
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
