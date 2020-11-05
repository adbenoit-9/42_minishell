/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/05 23:37:28 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stocknclear(t_stock **cmd_lst, int n)
{
	while (n > 0)
	{
		*cmd_lst = (*cmd_lst)->next;
		--n;
	}
	if ((*cmd_lst)->next && ((*cmd_lst)->next->sep == LEFT || (*cmd_lst)->next->sep == RIGHT || (*cmd_lst)->next->sep == D_RIGHT))
		stocknclear(&(*cmd_lst)->next, 0);
	clear_one(cmd_lst);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	t_stock	*cmd_lst;
	int		ret;
	size_t	i;

	(void)argc;
	(void)argv;
	erret = 0;
	while (1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		// ret = read(0, buffer, 4098);
		// buffer[ret] = 0;
		buffer = NULL;
		ret = get_next_line(0, &buffer);
		cmd_lst = NULL;
		i = 0;
		while (buffer[i] == ' ')
			++i;
		if (parse_str(buffer + i) == 0)
		{
			parsing(buffer, &cmd_lst, envp);
			// execute(&cmd_lst, envp);
			ft_stockclear(&cmd_lst, clear_one);
		}
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
