/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/11 19:46:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char *buffer;
	t_stock	*cmd_lst;
	// t_stock	*tmp;
	int	ret;
	// int i;

	(void)argc;
	(void)argv;
	while (1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, shell, 6);
		// ret = read(0, buffer, 4098);
		// buffer[ret] = 0;
		buffer = NULL;
		ret = get_next_line(0, &buffer);
		cmd_lst = NULL;
		parsing(buffer, &cmd_lst, envp);
		// tmp = cmd_lst;
		// while (tmp)
		// {
		// 	i = -1;
		// 	while (tmp->input && tmp->input[++i])
		// 		printf("[%s]\n", tmp->input[i]);
		// 	tmp = tmp->next;
		// 	printf("---------------\n");
		// }
		// ret = last_parsing(&cmd_lst);
		if (ret == -2)
		{
			//enlever les cmd redirige qui a fait failed
			//attention car si erreur apres faut pas le degager
		}
		// if (ret == 0)
		execute(&cmd_lst, envp);
		ft_stockclear(&cmd_lst, clear_one);
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
