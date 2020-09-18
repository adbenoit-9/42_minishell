/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/18 13:58:28 by adbenoit         ###   ########.fr       */
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

int				ft_issep(char c, char before)
{
	if (c != '>' && c != '<' && c != ';' && c != '|' && c != '&')
		return (0);
	if (before == '\\')
		return (0);
	return (1);
}
static size_t	define_len(char *str)
{
	size_t	len;
	char	quote;

	len = 0;
	while (str[len] && ft_issep(str[len], str[len - 1]) == 0)
	{
		quote = 0;
		if ((len == 0 || str[len - 1] != '\\') && (str[len] == '\"'
		|| str[len] == '\''))
		{
			quote = str[len];
			++len;
		}
		while (quote != 0 && str[len] && (str[len] != quote || (len != 0 &&
		str[len - 1] == '\\' && str[len - 2] != '\\' && str[len] == '\"')))
			++len;
		if (str[len])
			++len;
	}
	if (str[len - 1] == '\n')
		--len;
	return (len);
}

static char		*separate_cmd(char *cmd, int k, char *str, size_t *i)
{
	int		len;

	len = 0;
	if (k == UNKNOW)
	{
		while (str[len + *i] && ft_isspace(str[len + *i]) == 0)
			++len;
		if (str[len - 1] == '\n')
			--len;
		cmd = ft_strndup(str + *i, len);
		(*i) += len;
		while (ft_isspace(str[*i]) == 1)
			++(*i);
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
	input = NULL;
	unknow = separate_cmd(unknow, cmd, str, &i);
	len[0] = define_len(str + i);
	new->input = ft_strndup(str + i, len[0]);
	input = ft_strdup(new->input);
	len[0] += set_sep(str + i + len[0], &new);
	if (cmd != UNKNOW && new->input)
		set_input(input, &new, envp);
	if (new->input && (len[1] = ft_strlen(new->input)) != len[0])
	{
		if (!(new->input = ft_realloc(new->input, len[1] + 1)))
			ft_error(cmd_lst);
	}
	free(input);
	input = ft_strdup(new->input);
	if (unknow)
	{
		if (input && input[0])
		{
			unknow = ft_strjoin(unknow, " ");
			new->input = ft_strjoin(unknow, input);
		}
		else
			new->input = ft_strdup(unknow);
		free(unknow);
	}
	free(input);
	ft_stockadd_back(cmd_lst, new);
	if (str[len[0]])
		return (parsing(str + i + len[0], cmd_lst, envp));
	else
		return (0);
}
