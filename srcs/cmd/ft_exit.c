/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:33:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_stock **g_cmd, int i)
{
	if (ft_isdigit((*g_cmd)->tokens[1][i]) == 0 && (*g_cmd)->tokens[1][0] != '-'
	&& g_status == 0 && (*g_cmd)->tokens[1][0] != '0')
	{
		write_error("exit: ", (*g_cmd)->tokens[1],
		": numeric argument required\n", 1);
		return (1);
	}
	return (0);
}

void		ft_exit(t_stock **g_cmd, char *envp[])
{
	int	i;
	int	err;

	(void)envp;
	i = 0;
	write(1, "exit\n", 5);
	g_status = 0;
	if ((*g_cmd)->tokens[1])
	{
		g_status = ft_atoi((*g_cmd)->tokens[1]);
		while ((*g_cmd)->tokens[1][i])
		{
			if ((err = print_error(g_cmd, i)) > 0)
				break ;
			++i;
		}
		if (err == 0 && (*g_cmd)->tokens[2])
		{
			write_error("exit: ", "", "too many arguments\n", 1);
			(*g_cmd)->err = EXIT_ERROR;
			return ;
		}
	}
	ft_stockclear(g_cmd, clear_one);
	exit(EXIT_SUCCESS);
}
