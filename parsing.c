/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:02:57 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/26 01:36:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unknow_command(char *input, t_list *order)
{
	(void)input;
	(void)order;
	return (0);
}

int parsing(char *input, t_list **order)
{
    int 				i;
	size_t				size;
    char				*commands[7] = {"echo ", "cd ", "pwd ", "env ",
									"export ", "unset ", "exit "};

    i = 0;
    while (i < 7)
    {
		size = ft_strlen(commands[i]);
        if (ft_strncmp(commands[i], input, size) == 0)
            return (init_lst(input + size, order, i));
        i++;
    }
	if (i == 7)
		return (unknow_command(input, *order));
    return (0);
}
