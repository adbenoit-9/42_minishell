/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/26 01:55:37 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_sep(char *input, t_list **order)
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
			(*order)->sep = i;
			while (input[size] == ' ')
				++size;
			return (size);
		}
		i++;
	}
	(*order)->sep = NONE;
	return (0);
}

int			init_lst(char *input, t_list **order, int command)
{
	int i;
	int size;
	t_list *new;

	new = ft_lstnew(command);
	size = -1;
	while (input[size] &&  input[size] != '>' && input[size] != '<' &&
	input[size] != ';' && input[size] != '|' && ft_strncmp(input + size, "&&", 2) != 0)
		++size;
	if (!(new->input = malloc(size + 1)) || !(new->output = malloc(size + 1)))
		return (ft_error(new));
	i = -1;
	while (++i < size)
		new->input[i] = input[i];
	new->input[i] = 0;
	i += init_sep(input + i, &new);
	set_output(new->input, &new->output);
	ft_lstadd_back(order, new);
	if (input[i])
		return (parsing(input + i, order));
	else
		return (0);
}
