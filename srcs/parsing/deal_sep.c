/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:41:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 14:01:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sep(char *str, size_t *i)
{
	static char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>"};
	int			s;
	int			size;
	int			end;

	s = 0;
	if (!str || !str[0])
		return (-1);
	end = ft_strlen(str) < 2 ? 4 : NUM_SEP;
	while (s < end)
	{
		size = s < 4 ? 1 : 2;
		if (ft_strncmp(sep[s], str, size) == 0)
			break ;
		++s;
	}
	if (s > -1)
		*i += size;
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
