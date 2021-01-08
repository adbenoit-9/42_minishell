/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 13:58:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error(int i, t_list *lst, unsigned long long int *nb)
{
	unsigned long long int x;

	x = 9223372036854775807;
	if (ft_isdigit(lst->content[i]) == 0)
	{
		error_msg("exit: ", lst->content,
		": numeric argument required\n", 2);
		return (1);
	}
	*nb = (*nb * 10) + lst->content[i] - '0';
	if ((lst->content[0] == '-' && *nb > x + 1) ||
	(lst->content[0] != '-' && *nb > x))
	{
		error_msg("exit: ", lst->content,
		": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

static int	check_arg(t_list *lst, t_cmd *cmd)
{
	int						err;
	int						i;
	unsigned long long int	nb;

	nb = 0;
	i = 0;
	if (lst->content && (lst->content[0] == '-' || lst->content[0] == '+'))
		++i;
	while (lst->content[i])
	{
		if ((err = exit_error(i, lst, &nb)) > 0)
			return (0);
		++i;
	}
	if (err == 0 && lst->next)
	{
		error_msg("exit: ", NULL, "too many arguments\n", 1);
		cmd->err = EXIT_ERROR;
		return (1);
	}
	return (0);
}

void		ft_exit(t_cmd *cmd, int *fd, char **envp[])
{
	int	ret;

	(void)fd;
	(void)envp;
	ret = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd->tok->next)
	{
		g_status = ft_atoi(cmd->tok->next->content);
		ret = check_arg(cmd->tok->next, cmd);
	}
	if (ret == 1)
		return ;
	ft_cmdclear(&g_cmd, clear_one);
	ft_freetab(*envp);
	exit(g_status);
}
