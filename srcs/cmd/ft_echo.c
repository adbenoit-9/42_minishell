/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/18 14:06:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	n;

	(void)envp;
	i = 0;
	n = 0;
	while (ft_strncmp((*cmd_lst)->input + i, "-n ", 3) == 0)
	{
		++n;
		i += 3;
	}
	if (n > 0)
		(*cmd_lst)->output = ft_strdup((*cmd_lst)->input + i);
	else
		(*cmd_lst)->output = ft_strjoin((*cmd_lst)->input, "\n");
	if (!((*cmd_lst)->output))
		ft_error(cmd_lst);
	(*cmd_lst)->ret = 0;
}
