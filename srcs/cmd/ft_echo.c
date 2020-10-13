/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/12 16:27:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo_n(t_stock **cmd_lst, int *i)
{
	int	n;

	n = 0;
	while (ft_strncmp((*cmd_lst)->input[0] + *i, "-n ", 3) == 0)
	{
		++n;
		*i += 3;
	}
	if (ft_strncmp((*cmd_lst)->input[0] + *i, "-n", 2) == 0)
	{
		*i += 2;
		++n;
		while ((*cmd_lst)->input[0][*i] == 'n')
			++(*i);
	}
	return (n);
}

void	ft_echo(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int k;
	int	fd;

	(void)envp;
	i = 0;
	fd = 1;
	if (!(*cmd_lst)->input || ft_redirect(cmd_lst, &fd, 0) == -1)
		return ;
	if (ft_echo_n(cmd_lst, &i) > 0)
	{
		k = 0;
		while ((*cmd_lst)->input[++k])
		{
			write(fd, (*cmd_lst)->input[k], ft_strlen((*cmd_lst)->input[k]));
			write(1, " ", 1);
		}
	}
	else
	{
		k = -1;
		while ((*cmd_lst)->input[++k])
		{
			write(fd, (*cmd_lst)->input[k], ft_strlen((*cmd_lst)->input[k]));
			write(1, " ", 1);
		}
		write(fd, "\n", 1);
	}
	if (fd != 1)
		close(fd);
	(*cmd_lst)->ret = 0;
}
