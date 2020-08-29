/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/08/29 17:29:36 by adbenoit         ###   ########.fr       */
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
	printf("%sOur output:%s\n", "\033[1;4;34m", "\033[0m");
	while (tmp)
	{
		printf("%s\n", tmp->output);
		tmp = tmp->next;
	}
	printf("%sReal output:%s\n", "\033[1;4;34m", "\033[0m");
	system(buffer);
	return (0);
}
