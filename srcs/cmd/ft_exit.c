/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 17:22:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_stock **cmd_lst, char *envp[])
{
	int		i;
	char	*err;
	// int value;

	i = 0;
	(void)envp;
	(*cmd_lst)->output = ft_strdup("exit\n");
	while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '\n')
	{
		if (((*cmd_lst)->input[i] < '0' || (*cmd_lst)->input[i] > '9')
		&& (*cmd_lst)->input[0] != '-')
		{
			err = output_error("exit: ", (*cmd_lst)->input,
			": numeric argument required\n");
			(*cmd_lst)->output = ft_strjoin((*cmd_lst)->output, err);
			free(err);
			break ;
		}
		++i;
	}
	// value = atoi((*cmd_lst)->input);
	printf("%soutput:%s\n", "\033[1;4;34m", "\033[0m");
	printf("%s", (*cmd_lst)->output);
	exit(EXIT_SUCCESS);
}
