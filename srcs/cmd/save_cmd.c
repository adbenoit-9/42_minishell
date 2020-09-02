/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/02 20:29:14 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_sep(char *str, t_list **cmd_lst)
{
	char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>", "<<", "&&", "||"};
	int	 i;
	int	 size;

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
	size_t size;
	char quote;

	size = 0;
	while (str[size] == ' ')
		++size;
	while (str[size] &&  str[size] != '>' && str[size] != '<' &&
	str[size] != ';' && str[size] != '|' && ft_strncmp(str + size, "&&", 2) != 0)
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
	return (size);
}

int			save_cmd(char *str, t_list **cmd_lst, int cmd)
{
	size_t	i;
	size_t	size;
	t_list	*new;
	int		j;

	new = ft_listnew(cmd);
	size = define_size(str);
	if (!(new->input = malloc(size + 1)))
		return (ft_error(*cmd_lst));
	i = -1;
	j = 0;
	while (str[j] == ' ')
		++j;
	while (++i < size - 1)
		new->input[i] = str[j + i];
	new->input[i] = 0;
	if (i != 0 && new->input[i - 1] == '\n')
		new->input[i - 1] = 0;
	i += set_sep(str + j + i, &new);
	if (cmd != UNKNOW)
		set_input(new->input, &new->input);
	ft_listadd_back(cmd_lst, new);
	if (str[i])
		return (parsing(str + j + i, cmd_lst));
	else
		return (0);
}
