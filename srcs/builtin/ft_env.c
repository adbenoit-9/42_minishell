/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 01:56:24 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arenvp(t_cmd **cmd)
{
	int	ret;

	ret = 0;
	if ((*cmd)->tokens[1] != NULL)
	{
		ret = 1;
		write(2, "env: ", 5);
		write(2, (*cmd)->tokens[1], ft_strlen((*cmd)->tokens[1]));
		write(2, ": No argument required\n", 24);
		g_status = 127;
	}
	return (ret);
}


void		ft_env(t_cmd **cmd, int *fd, char *envp[])
{
	int		index;
	int		i;

	if (ft_arenvp(cmd) == 1)
		return ;
	index = 0;
	while (envp[index])
	{
		i = 0;
		while (envp[index][i])
			++i;
		if (envp[index][i - 1] != '=')
		{
			ft_putstr_fd(envp[index], fd[1]);
			write(fd[1], "\n", 1);
		}
		++index;
	}
	return ;
}
