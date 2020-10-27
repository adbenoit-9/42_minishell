/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/27 13:37:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, int *s)
{
	static char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>"};
	int			i;
	int			size;
	int			end;

	i = 0;
	if (!str || !str[i])
	{
		*s = -1;
		return (0);
	}
	end = ft_strlen(str) < 2 ? 4 : NUM_SEP;
	while (i < end)
	{
		size = i < 4 ? 1 : 2;
		if (ft_strncmp(sep[i], str, size) == 0)
			*s = i;
		++i;
	}
	if (*s == -1)
		return (0);
	if (*s == 4)
		return (2);
	return (1);
}

int	ft_issep(char c, char before)
{
	if (c != '>' && c != '<' && c != ';' && c != '|')
		return (0);
	if (before == '\\')
		return (0);
	return (1);
}

int	sep_error(int s1, int s2, int i)
{
	if (s1 != NONE && (s2 != NONE || i == 0))
	{
		write_error("", "syntax error\n", "", 258);
		return (-1);
	}
	return (0);
}
