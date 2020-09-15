/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/09/15 20:28:33 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char buffer[4098];
	t_stock	*cmd_lst;
	t_stock	*tmp;
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
		execute(&cmd_lst, envp);
		tmp = cmd_lst;
		printf("%sinput:%s\n", "\033[1;4;34m", "\033[0m");
		while (tmp)
		{
			printf("%s\n", tmp->input);
			tmp = tmp->next;
		}
		tmp = cmd_lst;
		printf("%soutput:%s\n", "\033[1;4;34m", "\033[0m");
		while (tmp)
		{
			printf("%s", tmp->output);
			tmp = tmp->next;
		}
		ft_stockclear(&cmd_lst, clear_one);
		// printf("%p\n", cmd_lst);
		// printf("%sReal input:%s\n", "\033[1;4;34m", "\033[0m");
		// system(buffer);
	}
	return (0);
}
