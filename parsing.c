/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:02:57 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/26 02:19:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unknow_cmd(char *input, t_list *cmd_lst)
{
	(void)input;
	(void)cmd_lst;
	return (0);
}

int parsing(char *input, t_list **cmd_lst)
{
    int 				i;
	size_t				size;
    char				*cmd_str[7] = {"echo ", "cd ", "pwd ", "env ",
									"export ", "unset ", "exit "};

    i = 0;
    while (i < NUM_CMD)
    {
		size = ft_strlen(cmd_str[i]);
        if (ft_strncmp(cmd_str[i], input, size) == 0)
            return (save_cmd(input + size, cmd_lst, i));
        i++;
    }
	if (i == NUM_CMD)
		return (unknow_cmd(input, *cmd_lst));
    return (0);
}
