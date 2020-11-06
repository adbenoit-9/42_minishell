/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 00:27:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(int i, t_stock *cmd)
{
	if (ft_isdigit(cmd->tokens[1][i]) == 0 && cmd->tokens[1][0] != '-'
	&& g_status == 0 && cmd->tokens[1][0] != '0')
	{
		write_error("exit: ", cmd->tokens[1],
		": numeric argument required\n", 1);
		return (1);
	}
	return (0);
}

void		ft_exit(t_stock **cmd, char *envp[])
{
	int	i;
	int	err;

	(void)envp;
	i = 0;
	write(1, "exit\n", 5);
	g_status = 0;
	if ((*cmd)->tokens[1])
	{
		g_status = ft_atoi((*cmd)->tokens[1]);
		while ((*cmd)->tokens[1][i])
		{
			if ((err = print_error(i, *cmd)) > 0)
				break ;
			++i;
		}
		if (err == 0 && (*cmd)->tokens[2])
		{
			write_error("exit: ", "", "too many arguments\n", 1);
			(*cmd)->err = EXIT_ERROR;
			return ;
		}
	}
	ft_stockclear(cmd, clear_one);
	exit(EXIT_SUCCESS);
}
