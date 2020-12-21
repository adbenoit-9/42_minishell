/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/21 18:54:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, int *i)
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

int	ft_issep(char c)
{
	if (c != '>' && c != '<' && c != ';' && c != '|')
		return (0);
	return (1);
}

int	sep_error(int s1, int s2, char *str)
{
	int ret;

	ret = 0;
	if (!str[0] && ((s1 == COMA && s2 != NONE) || (s1 != COMA && s1 != NONE)))
		ret = -1;
	else if (s1 == COMA && (s2 == RIGHT || s2 == LEFT || s2 == D_RIGHT))
		return (0);
	if (ret == -1 || (s1 != NONE && s2 != NONE))
	{
		error_msg(NULL, NULL, "syntax error\n", 2);
		return (-1);
	}
	return (0);
}
