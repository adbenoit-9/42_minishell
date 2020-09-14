/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 17:20:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_stock **cmd_lst, char *envp[])
{
	int	i;

	(void)envp;
	i = 0;
	if (ft_strncmp((*cmd_lst)->input, "-n ", 3) == 0)
		(*cmd_lst)->output = ft_strdup((*cmd_lst)->input + 3);
	else
		(*cmd_lst)->output = ft_strjoin((*cmd_lst)->input, "\n");
	(*cmd_lst)->ret = 0;
}
