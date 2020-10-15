/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/15 17:03:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, t_stock **cmd_lst)
{
	static char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>"};
	int			i;
	int			size;
	int			end;

	i = 0;
	end = ft_strlen(str) < 2 ? 4 : NUM_SEP;
	while (i < end)
	{
		size = i < 4 ? 1 : 2;
		if (ft_strncmp(sep[i], str, size) == 0)
			(*cmd_lst)->sep = i;
		i++;
	}
	if ((*cmd_lst)->sep == -1)
		return (0);
	if ((*cmd_lst)->sep == 4)
		return (2);
	return (1);
}

int	ft_issep(char c, char before)
{
	if (c != '>' && c != '<' && c != ';' && c != '|' && c != '&')
		return (0);
	if (before == '\\')
		return (0);
	return (1);
}

int	sep_error(int sep, int sep_before)
{
	static char	*sep_lst[5] = {"|", ";", ">", "<", ">>"};

	if (sep_before > 1 && ((sep == sep_before && sep != 4) || sep == NONE))
	{
		write_error("", "", "syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (sep == sep_before && sep != NONE)
	{
		write_error("", "syntax error near unexpected token `", "");
		write(1, sep_lst[sep], 1);
		write(1, sep_lst[sep], 1);
	}
	else if (sep_before < 2 && sep_before != NONE)
	{
		write_error("", "syntax error near unexpected token `", "");
		write(1, sep_lst[sep_before], 1);
	}
	else if (sep_before > 1 && sep < 2)
	{
		write_error("", "syntax error near unexpected token `", "");
		write(1, sep_lst[sep], 1);
	}
	else
		return (0);
	// else if ()
	// {
	// 	write_error("", "syntax error near unexpected token `", "");
	// 	write(1, char[sep], 1);
	// }
	write(1, "'\n", 2);
	return (0);
}
