/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/16 15:29:09 by adbenoit         ###   ########.fr       */
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
		return (size);
	return (size - 1);
}

int				save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[])
{
	size_t	i;
	size_t	size;
	size_t	len;
	char	*input;
	t_stock	*new;

	new = ft_stocknew(cmd);
	i = 0;
	while (str[i] == ' ')
		++i;
	size = define_size(str + i);
	if (!(new->input = malloc(size + 1)))
		return (ft_error(cmd_lst));
	ft_strncpy(new->input, str + i, size);
	new->input[size] = 0;
	input = ft_strdup(new->input);
	size += set_sep(str + i + size, &new);
	if (cmd != UNKNOW)
		set_input(input, &new, envp);
	if ((len = ft_strlen(new->input)) != size)
	{
		if (!(new->input = ft_realloc(new->input, len + 1)))
			ft_error(cmd_lst);
	}
	ft_stockadd_back(cmd_lst, new);
	if (str[size])
		return (parsing(str + i + size, cmd_lst, envp));
	else
		return (0);
}
