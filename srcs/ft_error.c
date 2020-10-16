/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/16 14:29:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_one(t_stock **cmd_lst)
{
	free((*cmd_lst)->input);
	free((*cmd_lst)->stdin);
	free((*cmd_lst)->stdout);
	(*cmd_lst)->input = NULL;
	(*cmd_lst)->stdin = NULL;
	(*cmd_lst)->stdout = NULL;
}

int		ft_error(t_stock **cmd_lst)
{
	char	*err;

	ft_stockclear(cmd_lst, clear_one);
	err = ft_strjoin("minishell: ", strerror(errno));
	write(1, err, ft_strlen(err));
	return (0);
}

int		write_error(char *cmd, char *arg, char *err)
{
	write(1, "minishell: ", 11);
	write(1, cmd, ft_strlen(cmd));
	write(1, arg, ft_strlen(arg));
	write(1, err, ft_strlen(err));
	return (0);
}
