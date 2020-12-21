/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/21 04:39:41 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(int i, t_cmd *cmd, unsigned long long int *nb)
{
	unsigned long long int x;

	x = 9223372036854775807;
	if (ft_isdigit(cmd->tokens[1][i]) == 0)
	{
		error_msg("exit: ", cmd->tokens[1],
		": numeric argument required\n", 255);
		return (1);
	}
	*nb = (*nb * 10) + cmd->tokens[1][i] - '0';
	if ((cmd->tokens[1][0] == '-' && *nb > x + 1) ||
	(cmd->tokens[1][0] != '-' && *nb > x))
	{
		error_msg("exit: ", cmd->tokens[1],
		": numeric argument required\n", 255);
		return (1);
	}
	return (0);
}

static int	check_arg(t_cmd **cmd)
{
	int						err;
	int						i;
	unsigned long long int	nb;

	nb = 0;
	i = 0;
	if ((*cmd)->tokens[1] && ((*cmd)->tokens[1][0] == '-'
	|| (*cmd)->tokens[1][0] == '+'))
		++i;
	while ((*cmd)->tokens[1][i])
	{
		if ((err = exit_error(i, *cmd, &nb)) > 0)
			return (0);
		++i;
	}
	if (err == 0 && (*cmd)->tokens[2])
	{
		error_msg("exit: ", NULL, "too many arguments\n", 1);
		(*cmd)->err = EXIT_ERROR;
		return (1);
	}
	return (0);
}

void		ft_exit(t_cmd **cmd, char *envp[], int *fd)
{
	int	ret;

	(void)envp;
	(void)fd;
	ret = 0;
	write(1, "exit\n", 5);
	if ((*cmd)->tokens[1])
	{
		g_status = ft_atoi((*cmd)->tokens[1]);
		ret = check_arg(cmd);
	}
	if (ret == 1)
		return ;
	ft_cmdclear(&g_cmd, clear_one);
	exit(g_status);
}
