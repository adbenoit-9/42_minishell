/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/18 16:18:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_stock **cmd_lst, int i)
{
	char	*err;

	if (ft_isdigit((*cmd_lst)->input[i]) == 0 && (*cmd_lst)->input[0] != '-'
	&& (*cmd_lst)->ret == 0 && (*cmd_lst)->input[0] != '0')
	{
		err = output_error("exit: ", (*cmd_lst)->input,
		": numeric argument required\n");
		(*cmd_lst)->output = ft_strjoin((*cmd_lst)->output, err);
		free(err);
		return (1);
	}
	if (ft_isdigit((*cmd_lst)->input[i]) == 0 && (*cmd_lst)->input[i] != '-'
	&& (*cmd_lst)->ret != 0)
	{
		err = output_error("exit: ", "",
		"too many arguments\n");
		(*cmd_lst)->output = ft_strjoin((*cmd_lst)->output, err);
		free(err);
		return (2);
	}
	return (0);
}

void		ft_exit(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	err;

	i = 0;
	(void)envp;
	(*cmd_lst)->output = ft_strdup("exit\n");
	(*cmd_lst)->ret = ft_atoi((*cmd_lst)->input);
	while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '\n')
	{
		if ((err = print_error(cmd_lst, i)) > 0)
			break ;
		++i;
	}
	if (err != 2)
		exit(EXIT_SUCCESS);
}
