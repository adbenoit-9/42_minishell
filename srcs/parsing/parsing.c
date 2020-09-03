/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 22:27:37 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/03 22:27:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(char *str, t_list **cmd_lst)
{
    int		i;
    int		j;
	size_t	size;
    char	*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

    i = 0;
    j = 0;
    while (str[j] == ' ')
        ++j;
    while (str[j] && i < NUM_CMD)
    {
		size = ft_strlen(cmd_str[i]);
        if (ft_strncmp(cmd_str[i], str + j, size) == 0 &&
		(str[j + size] == ' ' || str[j + size] == '\n'))
            return (save_cmd(str + j + size, cmd_lst, i));
        i++;
    }
	if (str[j] && str[j] != '\n' && i == UNKNOW)
		return (save_cmd(str + j, cmd_lst, i));
	return (0);
}
