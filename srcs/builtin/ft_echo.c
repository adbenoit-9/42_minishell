/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/30 19:42:04 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd, int *fd, char **envp[])
{
	int		n;
	int		j;
	t_list	*tmp;

	(void)envp;
	tmp = cmd->tok;
	n = 0;
	while ((tmp = (tmp)->next) && ft_strncmp((tmp)->content, "-n", 2) == 0)
	{
		j = 2;
		while ((tmp)->content[j] == 'n')
			++j;
		if ((tmp)->content[j])
			break ;
		++n;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->content, fd[1]);
		if ((tmp = tmp->next))
			write(fd[1], " ", 1);
	}
	if (n == 0)
		write(fd[1], "\n", 1);
	return ;
}
