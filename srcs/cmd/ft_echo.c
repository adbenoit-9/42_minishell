/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/09 11:59:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_n(t_stock *cmd, int *i)
{
	int	n;
	int j;

	n = 0;
	if (!cmd->tokens[0])
		return (0);
	while (cmd->tokens[*i] && ft_strncmp(cmd->tokens[*i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->tokens[*i][j] == 'n')
			++j;
		if (cmd->tokens[*i][j])
			return (n);
		++n;
		++(*i);
	}
	return (n);
}

void		ft_echo(t_stock **cmd, char *envp[], int *fd)
{
	int	i;
	int k;
	int n;

	(void)envp;
	i = 1;
	if (!(*cmd)->tokens)
		return ;
	n = ft_echo_n(*cmd, &i);
	k = i - 1;
	while ((*cmd)->tokens[++k])
	{
		if (k != i)
			write(fd[1], " ", 1);
		write(fd[1], (*cmd)->tokens[k], ft_strlen((*cmd)->tokens[k]));
	}
	if (n == 0)
		write(fd[1], "\n", 1);
	return ;
}
