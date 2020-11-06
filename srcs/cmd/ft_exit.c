/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 14:19:13 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_stock **cmd_lst, int i)
{
	if (ft_isdigit((*cmd_lst)->tokens[1][i]) == 0 && (*cmd_lst)->tokens[1][0] != '-'
	&& erret == 0 && (*cmd_lst)->tokens[1][0] != '0')
	{
		write_error("exit: ", (*cmd_lst)->tokens[1],
		": numeric argument required\n", 1);
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
	erret = 0;
	if ((*cmd_lst)->tokens[1])
	{
		erret = ft_atoi((*cmd_lst)->tokens[1]);
		while ((*cmd_lst)->tokens[1][i])
		{
			if ((err = print_error(cmd_lst, i)) > 0)
				break ;
			++i;
		}
		if (err == 0 && (*cmd_lst)->tokens[2])
		{
			write_error("exit: ", "", "too many arguments\n", 1);
			(*cmd_lst)->err = EXIT_ERROR;
			return ;
		}
	}
	ft_stockclear(cmd_lst, clear_one);
	exit(EXIT_SUCCESS);
}
