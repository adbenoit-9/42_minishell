/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/21 18:28:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_one(t_stock **cmd_lst)
{
	free((*cmd_lst)->input);
	(*cmd_lst)->input = NULL;
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
