/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/26 02:59:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_sep(char *input, t_list **cmd_lst)
{
	char	*sep[NUM_SEP] = {"|", ";", ">", "<", ">>", "<<", "&&", "||"};
	int	 i;
	int	 size;

	i = 0;
	while (i < NUM_SEP)
	{
		size = i < 4 ? 1 : 2;
		if (ft_strncmp(sep[i], input, size) == 0)
		{
			(*cmd_lst)->sep = i;
			while (input[size] == ' ')
				++size;
			return (size);
		}
		i++;
	}
	(*cmd_lst)->sep = NONE;
	return (0);
}

int			save_cmd(char *input, t_list **cmd_lst, int cmd)
{
	int i;
	int size;
	t_list *new;

	new = ft_lstnew(cmd);
	size = -1;
	while (input[size] &&  input[size] != '>' && input[size] != '<' &&
	input[size] != ';' && input[size] != '|' && ft_strncmp(input + size, "&&", 2) != 0)
		++size;
	if (!(new->input = malloc(size + 1)) || !(new->output = malloc(size + 1)))
		return (ft_error(cmd_lst));
	i = -1;
	while (++i < size)
		new->input[i] = input[i];
	new->input[i] = 0;
	i += set_sep(input + i, &new);
	set_output(new->input, &new->output);
	ft_lstadd_back(cmd_lst, new);
	if (input[i])
		return (parsing(input + i, cmd_lst));
	else
		return (0);
}
