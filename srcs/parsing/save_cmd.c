/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/17 16:07:30 by adbenoit         ###   ########.fr       */
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

static size_t	define_len(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	while (str[size] && str[size] != '>' && str[size] != '<' && str[size]
	!= ';' && str[size] != '|' && ft_strncmp(str + size, "&&", 2) != 0)
	{
		quote = 0;
		if ((size == 0 || str[size - 1] != '\\') && (str[size] == '\"'
		|| str[size] == '\''))
		{
			quote = str[size];
			++size;
		}
		while (quote != 0 && str[size] && (str[size] != quote || (size != 0 &&
		str[size - 1] == '\\' && str[size - 2] != '\\' && str[size] == '\"')))
			++size;
		if (str[size])
			++size;
	}
	if (str[size])
		return (size);
	return (size - 1);
}

static char		*separate_cmd(char *cmd, int k, char *str, size_t *i)
{
	int		len;

	len = 0;
	if (k == UNKNOW)
	{
		while (str[len + *i] && str[len + *i] != ' ')
			++len;
		if (str[*i] == ' ')
			++len;
		++len;
		cmd = ft_strndup(str + *i, len);
		(*i) += len;
	}
	return (cmd);
}

int				save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[])
{
	size_t	i;
	char	*unknow;
	size_t	len[2];
	char	*input;
	t_stock	*new;

	new = ft_stocknew(cmd);
	i = 0;
	while (str[i] == ' ')
		++i;
	unknow = NULL;
	unknow = separate_cmd(unknow, cmd, str, &i);
	len[0] = define_len(str + i);
	new->input = ft_strndup(str + i, len[0]);
	input = ft_strdup(new->input);
	len[0] += set_sep(str + i + len[0], &new);
	if (cmd != UNKNOW)
		set_input(input, &new, envp);
	if ((len[1] = ft_strlen(new->input)) != len[0])
	{
		if (!(new->input = ft_realloc(new->input, len[1] + 1)))
			ft_error(cmd_lst);
	}
	free(input);
	input = ft_strdup(new->input);
	if (unknow)
		new->input = ft_strjoin(unknow, input);
	free(input);
	free(unknow);
	ft_stockadd_back(cmd_lst, new);
	if (str[len[0]])
		return (parsing(str + i + len[0], cmd_lst, envp));
	else
		return (0);
}
