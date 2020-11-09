/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/09 16:06:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(int i, t_stock *cmd)
{
	if (ft_isdigit(cmd->tokens[1][i]) == 0 && cmd->tokens[1][0] != '-'
	&& g_status == 0 && cmd->tokens[1][0] != '0')
	{
		print_error("exit: ", cmd->tokens[1],
		": numeric argument required\n", 1);
		return (1);
	}
	return (0);
}

void		ft_exit(t_stock **cmd, char *envp[], int *fd)
{
	int	i;
	int	err;

	(void)envp;
	i = 0;
	(void)fd;
	write(1, "exit\n", 5);
	if ((*cmd)->tokens[1])
	{
		g_status = ft_atoi((*cmd)->tokens[1]);
		while ((*cmd)->tokens[1][i])
		{
			if ((err = exit_error(i, *cmd)) > 0)
				break ;
			++i;
		}
		if (err == 0 && (*cmd)->tokens[2])
		{
			print_error("exit: ", NULL, "too many arguments\n", 1);
			(*cmd)->err = EXIT_ERROR;
			return ;
		}
	}
	ft_stockclear(cmd, clear_one);
	exit(g_status);
}
