/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/31 02:32:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_error(t_list *lst)
{
	int	ret;

	ret = 0;
	if (lst != NULL)
	{
		ret = 1;
		error_msg("env", NULL, ": No argument required\n", 127);
	}
	return (ret);
}

void		ft_env(t_cmd *cmd, int *fd, char **envp[])
{
	int		index;
	int		i;

	if (ft_env_error(cmd->tok->next) == 1)
		return ;
	index = 0;
	while ((*envp)[index])
	{
		i = 0;
		while ((*envp)[index][i] && (*envp)[index][i] != '=')
			++i;
		if ((*envp)[index][i])
		{
			ft_putstr_fd((*envp)[index], fd[1]);
			write(fd[1], "\n", 1);
		}
		++index;
	}
	return ;
}
