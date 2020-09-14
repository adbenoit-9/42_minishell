/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:17:06 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 17:17:58 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_stock **cmd_lst, char *envp[])
{
	int					i;
	static t_function	cmd_fct[NUM_CMD] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit};

	i = 0;
	if (!(*cmd_lst))
		return ;
	while (*cmd_lst && i < NUM_CMD && (*cmd_lst)->cmd != i)
		++i;
	if (i == NUM_CMD)
		return ;
	if (*cmd_lst && (*cmd_lst)->cmd != UNKNOW)
		cmd_fct[i](cmd_lst, envp);
	if ((*cmd_lst)->next)
		execute(&(*cmd_lst)->next, envp);
}
