/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/25 16:45:15 by adbenoit         ###   ########.fr       */
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
		cmd = ft_strndup(str + *i, len);
		(*i) += len;
		while (ft_isspace(str[*i]) == 1 && str[*i] != '\n')
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

static size_t	input_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		++len;
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
	len[0] = input_len(str + i);
	if (!(new->input = malloc(len[0] + 1)))
		ft_error(cmd_lst);
	i += (size_t)set_input(str + i, &new, envp);
	if (new->input && (len[1] = ft_strlen(new->input)) != len[0])
		new->input = ft_realloc(new->input, len[1] + 1);
	free(input);
	add_unknow_cmd(input, &new->input, unknow);
	ft_stockadd_back(cmd_lst, new);
	if (str[i])
		return (parsing(str + i, cmd_lst, envp));
	else
		return (0);
}
