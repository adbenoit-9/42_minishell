/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/25 13:40:22 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, t_stock **cmd_lst)
{
	static char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>", "<<", "&&", "||"};
	int			i;
	int			size;

	i = 0;
	while (i < NUM_SEP)
	{
		size = i < 4 ? 1 : 2;
		if (ft_strncmp(sep[i], str, size) == 0)
		{
			(*cmd_lst)->sep = i;
			while (str[size] == ' ')
				++size;
			return (size);
		}
		i++;
	}
	(*cmd_lst)->sep = NONE;
	return (0);
}

int	ft_issep(char c, char before)
{
	if (c != '>' && c != '<' && c != ';' && c != '|' && c != '&')
		return (0);
	if (before == '\\')
		return (0);
	return (1);
}

int	sep_error(t_stock **cmd_lst)
{
	if ((*cmd_lst)->input[0] == '<' || (*cmd_lst)->input[0] == '>')
	{
		write_error("", "", "syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (ft_issep((*cmd_lst)->input[0], 0) == 1)
	{
		write_error("", "syntax error near unexpected token `", "");
		if ((*cmd_lst)->input[1] == (*cmd_lst)->input[0])
			write(1, (*cmd_lst)->input, 2);
		else
			write(1, (*cmd_lst)->input, 1);
		write(1, "'\n", 2);
		return (1);
	}
	return (0);
}