/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:10:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/23 15:47:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *str, t_stock **cmd_lst, char *envp[])
{
	int			i;
	int			j;
	size_t		size;
	static char	*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

	i = 0;
	j = 0;
	while (str[j] == ' ' || str[j] == '\t')
		++j;
	while (str[j] && i < NUM_CMD)
	{
		size = ft_strlen(cmd_str[i]);
		if (ft_strncmp(cmd_str[i], str + j, size) == 0 && (ft_issep(str[j + size], 0) == 1 || ft_isspace(str[j + size]) == 1))
			return (save_cmd(str + j + size, cmd_lst, i, envp));
		i++;
	}
	if (str[j] && str[j] != '\n' && i == UNKNOW)
		return (save_cmd(str + j, cmd_lst, i, envp));
	return (0);
}
