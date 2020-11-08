/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/08 21:21:14 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, size_t *i)
{
	static char	sep[NUM_SEP] = "|;><";
	int			s;

	s = 0;
	if (!str || !str[0])
		return (-1);
	while (s < NUM_SEP && str[0] != sep[s])
		++s;
	++(*i);
	if (s == RIGHT && str[1] == '>')
	{
		++s;
		++(*i);
	}
	return (s);
}

int	ft_issep(char c, char before)
{
	if (c != '>' && c != '<' && c != ';' && c != '|')
		return (0);
	if (before == '\\')
		return (0);
	return (1);
}

int	sep_error(int s1, int s2)
{
	if (s1 != NONE && s2 != NONE)
	{
		print_error(NULL, NULL, "syntax error\n", 258);
		return (-1);
	}
	return (0);
}
