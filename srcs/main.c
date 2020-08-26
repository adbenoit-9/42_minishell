/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/08/26 16:11:55 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char buffer[4098];
	t_list	*cmd_lst;
	t_list	*tmp;
	int	ret;

	write(1, "\033[1mLesPetitsCoquillages", 27);
	write(1, shell, 6);
	// write(1, ": ", 2);
	ret = read(0, buffer, 4098);
	buffer[ret] = 0;
	cmd_lst = NULL;
	parsing(buffer, &cmd_lst);
	tmp = cmd_lst;
	while (tmp)
	{
		printf("output = %s\n", cmd_lst->output);
		tmp = cmd_lst->next;
	}
}
