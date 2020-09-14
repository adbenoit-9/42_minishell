/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 17:55:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_sep(char *str, t_stock **cmd_lst)
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

static size_t	define_size(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	while (str[size] && str[size] != '>' && str[size] != '<' && str[size]
	!= ';' && str[size] != '|' && ft_strncmp(str + size, "&&", 2) != 0)
	{
		quote = 0;
		if (str[size] == '\"' || str[size] == '\'')
		{
			quote = str[size];
			++size;
		}
		while (quote != 0 && str[size] && (str[size] != quote ||
		(size != 0 && str[size - 1] == '\\' && str[size] == quote)))
			++size;
		++size;
	}
	if (str[size])
		return (size + 1);
	return (size);
}

int				save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[])
{
	size_t	i;
	size_t	size;
	t_stock	*new;
	int		j;

	new = ft_stocknew(cmd);
	j = 0;
	while (str[j] == ' ')
		++j;
	size = define_size(str + j);
	if (!(new->input = malloc(size + 1)))
		return (ft_error(cmd_lst));
	i = -1;
	while (++i < size - 1)
		new->input[i] = str[j + i];
	new->input[i] = 0;
	i += set_sep(str + j + i, &new);
	if (cmd != UNKNOW)
		set_input(new->input, &new->input, envp);
	ft_stockadd_back(cmd_lst, new);
	if (str[i])
		return (parsing(str + j + i, cmd_lst, envp));
	else
		return (0);
}
