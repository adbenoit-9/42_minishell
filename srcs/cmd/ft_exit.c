/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/15 19:32:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_stock **cmd_lst, char *envp[])
{
	int		i;
	char	*err;

	i = 0;
	(void)envp;
	(*cmd_lst)->output = ft_strdup("exit\n");
	(*cmd_lst)->ret = ft_atoi((*cmd_lst)->input);
	while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '\n')
	{
		if (((*cmd_lst)->input[i] < '0' || (*cmd_lst)->input[i] > '9')
		&& (*cmd_lst)->input[0] != '-' && (*cmd_lst)->ret == 0 && (*cmd_lst)->input[0] != '0')
		{
			err = output_error("exit: ", (*cmd_lst)->input,
			": numeric argument required\n");
			(*cmd_lst)->output = ft_strjoin((*cmd_lst)->output, err);
			free(err);
			break ;
		}
		if (((*cmd_lst)->input[i] < '0' || (*cmd_lst)->input[i] > '9')
		&& (*cmd_lst)->input[i] != '-' && (*cmd_lst)->ret != 0)
		{
			err = output_error("exit: ", "",
			"too many arguments\n");
			(*cmd_lst)->output = ft_strjoin((*cmd_lst)->output, err);
			free(err);
			return ;
		}
		++i;
	}
	printf("%sinput:%s\n", "\033[1;4;34m", "\033[0m");
	printf("%s\n", (*cmd_lst)->input);
	printf("%soutput:%s\n", "\033[1;4;34m", "\033[0m");
	printf("%s", (*cmd_lst)->output);
	ft_stockclear(cmd_lst, clear_one);
	exit(EXIT_SUCCESS);
}
