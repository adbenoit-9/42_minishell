/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/21 19:06:33 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo_n(t_stock **cmd_lst, int *i)
{
	int	n;

	n = 0;
	while (ft_strncmp((*cmd_lst)->input + *i, "-n ", 3) == 0)
	{
		++n;
		i += 3;
	}
	if (ft_strncmp((*cmd_lst)->input + *i, "-n", 2) == 0)
	{
		*i += 2;
		++n;
		while ((*cmd_lst)->input[*i] == 'n')
			++i;
		if ((*cmd_lst)->input[*i] != '\t' && (*cmd_lst)->input[*i] != ' ')
			return (0);
		++i;
	}
	return (n);
}
void	ft_echo(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	fd;

	(void)envp;
	i = 0;
	fd = -1;
	if ((*cmd_lst)->sep == NONE || (*cmd_lst)->sep == COMA)
		fd = 1;
	// else if ((*cmd_lst)->sep == RIGHT)
	// 	fd = right_redirect(cmd_lst);
	if (fd == -1)
		return ;
	if (ft_echo_n(cmd_lst, &i) > 0)
		write(fd, (*cmd_lst)->input + i, ft_strlen((*cmd_lst)->input + i));
	else
	{
		write(fd, (*cmd_lst)->input, ft_strlen((*cmd_lst)->input));
		write(fd, "\n", 1);
	}
	if (fd != 1)
		close(fd);
	(*cmd_lst)->ret = 0;
}
