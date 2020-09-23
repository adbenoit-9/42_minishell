/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/23 14:39:45 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_stock **cmd_lst, int i)
{
	if (ft_isdigit((*cmd_lst)->input[i]) == 0 && (*cmd_lst)->input[0] != '-'
	&& (*cmd_lst)->ret == 0 && (*cmd_lst)->input[0] != '0')
	{
		write_error("exit: ", (*cmd_lst)->input,
		": numeric argument required\n");
		return (1);
	}
	if (ft_isdigit((*cmd_lst)->input[i]) == 0 && (*cmd_lst)->input[i] != '-'
	&& (*cmd_lst)->ret != 0)
	{
		write_error("exit: ", "",
		"too many arguments\n");
		return (2);
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
	(*cmd_lst)->ret = ft_atoi((*cmd_lst)->input);
	while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '\n')
	{
		if ((err = print_error(cmd_lst, i)) > 0)
			break ;
		++i;
	}
	if (err != 2)
	{
		ft_stockclear(cmd_lst, clear_one);
		exit(EXIT_SUCCESS);
	}
}
