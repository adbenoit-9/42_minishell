/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:24:24 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/22 16:24:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_stock **cmd_lst, char *envp[])
{
	int					i;
	static t_function	cmd_fct[NUM_CMD + 1] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit, ft_unknow};

	i = 0;
	if (*cmd_lst)
	{
		while (*cmd_lst && i < NUM_CMD && (*cmd_lst)->cmd != i)
			++i;
		cmd_fct[i](cmd_lst, envp);
		if ((*cmd_lst)->next && ((*cmd_lst)->sep == NONE ||
		(*cmd_lst)->sep == COMA))
			return (execute(&(*cmd_lst)->next, envp));
		else if ((*cmd_lst)->next && (*cmd_lst)->next->next
		&& (*cmd_lst)->sep != NONE && (*cmd_lst)->sep != COMA)
			return (execute(&(*cmd_lst)->next->next, envp));
	}
	return (0);
}
