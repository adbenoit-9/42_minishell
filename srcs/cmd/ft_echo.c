/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:33:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo_n(t_stock **g_cmd, int *i)
{
	int	n;
	int j;

	n = 0;
	if (!(*g_cmd)->tokens[1])
		return (0);
	while (ft_strncmp((*g_cmd)->tokens[*i], "-n", 2) == 0)
	{
		j = 2;
		while ((*g_cmd)->tokens[*i][j] == 'n')
			++j;
		if ((*g_cmd)->tokens[*i][j])
			return (n);
		++n;
		++(*i);
	}
	return (n);
}

void	ft_echo(t_stock **g_cmd, char *envp[])
{
	int	i;
	int k;
	int	fd;
	int n;

	(void)envp;
	i = 1;
	fd = 1;
	if (!(*g_cmd)->tokens)
		return ;
	ft_redirect(g_cmd, 0, &fd);
	n = ft_echo_n(g_cmd, &i);
	k = i - 1;
	while ((*g_cmd)->tokens[++k])
	{
		if (k != i)
			write(fd, " ", 1);
		if ((*g_cmd)->tokens[k][0] != VAR_NOT_FOUND)
			write(fd, (*g_cmd)->tokens[k], ft_strlen((*g_cmd)->tokens[k]));
	}
	if (n == 0)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	g_status = 0;
}
