/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/18 14:58:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_unknow_cmd(char *cmd, int k, char *str, size_t *i)
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

static void		add_unknow_cmd(char *input, char **new_input, char *cmd)
{
	if (cmd)
	{
		input = ft_strdup(*new_input);
		if (input && input[0])
		{
			cmd = ft_strjoin(cmd, " ");
			*new_input = ft_strjoin(cmd, input);
		}
		else
			*new_input = ft_strdup(cmd);
		free(cmd);
		free(input);
	}
}

static size_t	get_input(char *str, char **input, t_stock **new)
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
	(*new)->input = ft_strndup(str, len);
	*input = ft_strdup((*new)->input);
	len += set_sep(str + len, new);
	return (len);
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
	unknow = get_unknow_cmd(unknow, cmd, str, &i);
	len[0] = get_input(str + i, &input, &new);
	if (cmd != UNKNOW && new->input)
		set_input(input, &new, envp);
	if (new->input && (len[1] = ft_strlen(new->input)) != len[0])
		new->input = ft_realloc(new->input, len[1] + 1);
	free(input);
	add_unknow_cmd(input, &new->input, unknow);
	ft_stockadd_back(cmd_lst, new);
	if (str[len[0]])
		return (parsing(str + i + len[0], cmd_lst, envp));
	else
		return (0);
}
