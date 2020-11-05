/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:10:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/05 23:44:05 by adbenoit         ###   ########.fr       */
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
	int			i;
	int			j;
	size_t		size;
	int			ret;
	static char	*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

	j = 0;
	ft_stockclear(cmd_lst, clear_one);
	while (str[j] == ' ')
		++j;
	i = 0;
	ret = save_cmd(str + j, cmd_lst, envp);
	while (ret >= 0 && str[j] && i < NUM_CMD)
	{
		size = ft_strlen(cmd_str[i]);
		if (ft_strncmp(cmd_str[i], str + j, size) == 0 &&
		(ft_issep(str[j + size], 0) == 1 || ft_isspace(str[j + size]) == 1
		|| str[j + size] == 0))
		{
			(*cmd_lst)->cmd = i;
			break ;
		}
		i++;
	}
	if (*cmd_lst && (*cmd_lst)->sep == PIPE)
		ret = save_cmd(str + j + ret, &(*cmd_lst)->next, envp);
	if ((*cmd_lst)->err == 0)
		execute(cmd_lst, envp);
	if((*cmd_lst)->err != EXIT_ERROR && ret > 0 && str[ret + j])
		return (parsing(str + ret + j, cmd_lst, envp));
	return (0);
}
