/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/09/25 17:03:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char buffer[4098];
	t_stock	*cmd_lst;
	int	ret;

	(void)argc;
	(void)argv;
	while (1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, shell, 6);
		ret = read(0, buffer, 4098);
		buffer[ret] = 0;
		cmd_lst = NULL;
		parsing(buffer, &cmd_lst, envp);
		ret = last_parsing(&cmd_lst);
		if (ret == -2)
		{
			//enlever les cmd redirige qui a fait failed
			//attention car si erreur apres faut pas le degager
		}
		if (ret == 0)
			execute(&cmd_lst, envp);
		ft_stockclear(&cmd_lst, clear_one);
	}
	return (0);
}
