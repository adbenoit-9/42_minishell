/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/26 15:22:04 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_stock **cmd_lst, int i)
{
	if (ft_isdigit((*cmd_lst)->tokens[0][i]) == 0 && (*cmd_lst)->tokens[0][0] != '-'
	&& (*cmd_lst)->ret == 0 && (*cmd_lst)->tokens[0][0] != '0')
	{
		write_error("exit: ", (*cmd_lst)->tokens[0],
		": numeric argument required\n");
		return (1);
	}
	return (0);
}

void		ft_exit(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	err;

	(void)envp;
	i = 0;
	write(1, "exit\n", 5);
	if ((*cmd_lst)->tokens[0])
	{
		(*cmd_lst)->ret = ft_atoi((*cmd_lst)->tokens[0]);
		while ((*cmd_lst)->tokens[0][i])
		{
			if ((err = print_error(cmd_lst, i)) > 0)
				break ;
			++i;
		}
		if (err == 0 && (*cmd_lst)->tokens[1])
		{
			write_error("exit: ", "", "too many arguments\n");
			return ;
		}
	}
	ft_stockclear(cmd_lst, clear_one);
	exit(EXIT_SUCCESS);
}
