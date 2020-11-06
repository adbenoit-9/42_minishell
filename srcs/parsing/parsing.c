/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:10:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 15:58:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_error(t_stock **cmd_lst)
{
	int err;

	err = (*cmd_lst)->err;
	if (err >= -1)
		return (0);
	// ft_stockclear(new, clear_one);
	if (err == MALL_ERR)
		write_error("", strerror(errno), "\n", 1);
	else if (err == QUOTE_NOT_FOUND)
		write_error("", "syntax error : quote expected\n", "", 258);
	else if (err == ALONE_BS)
		write_error("", "syntax error : char expected\n", "", 258);
	else
		return (0);
	// ft_stockclear(cmd_lst, clear_one);
	return (err);
}

int		parse_str(char *str)
{
	size_t	i;
	int		quote;
	int 	s1;
	int		s2;
	int		tmp;

	i = 0;
	quote = 0;
	s1 = -1;
	while (str[i])
	{
		s2 = NONE;
		tmp = i;
		quote = is_in_quote(str, &i, quote);
		i = quote == 0 ? tmp : i;
		if (str[i] == '\\' && str[++i])
		{
			++i;
			s1 = NONE;
		}
		else if (str[i] && quote == 0 && ft_issep(str[i], 0) == 1)
		{
			if (s1 == NONE)
				i += set_sep(str + i, &s1);
			else if (s1 != NONE && str[i])
				i += set_sep(str + i, &s2);
			if ((!str[i] && s1 != COMA)|| i == 1)
				s2 = s1;
			if (sep_error(s1, s2) == -1)
				return (-1);
		}
		else if (str[i])
		{
			if (str[i] != ' ')
				s1 = NONE;
			++i;
		}
	}
	return (0);
}

int		parsing(char *str, t_stock **cmd_lst, char *envp[])
{
	int			ret;

	ft_stockclear(cmd_lst, clear_one);
	ret = save_cmd(str, cmd_lst, envp);
	if (ret > 0 && (*cmd_lst)->sep == PIPE)
		ret += save_cmd(str + ret, &(*cmd_lst)->next, envp);
	if ((*cmd_lst)->err == 0)
		execute(cmd_lst, envp);
	if((*cmd_lst)->err != EXIT_ERROR && ret > 0 && str[ret])
		return (parsing(str + ret, cmd_lst, envp));
	return (0);
}
