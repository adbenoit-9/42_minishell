/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/03 15:43:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(int i, t_stock *cmd, unsigned long long int *nb)
{
	unsigned long long int x;

	x = 9223372036854775807;
	if (ft_isdigit(cmd->tokens[1][i]) == 0)
	{
		print_error("exit: ", cmd->tokens[1],
		": numeric argument required\n", 255);
		return (1);
	}
	*nb = (*nb * 10) + cmd->tokens[1][i] - '0';
	if ((cmd->tokens[1][0] == '-' && *nb > x + 1) ||
	(cmd->tokens[1][0] != '-' && *nb > x))
	{
		print_error("exit: ", cmd->tokens[1],
		": numeric argument required\n", 255);
		return (1);
	}
	return (0);
}

void		ft_exit(t_stock **cmd, char *envp[])
{
	int	i;
	int	err;
	unsigned long long int nb;

	(void)envp;
	i = 0;
	nb = 0;
	write(2, "exit\n", 5);
	if ((*cmd)->tokens[1])
	{
		g_status = ft_atoi((*cmd)->tokens[1]);
		if ((*cmd)->tokens[1] && ((*cmd)->tokens[1][0] == '-' || (*cmd)->tokens[1][0] == '+'))
				++i;
		while ((*cmd)->tokens[1][i])
		{
			if ((err = exit_error(i, *cmd, &nb)) > 0)
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
	// system("leaks minishell");s
	exit(g_status);
}
