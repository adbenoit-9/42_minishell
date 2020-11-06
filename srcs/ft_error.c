/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:33:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_one(t_stock **g_cmd)
{
	free((*g_cmd)->tokens);
	free((*g_cmd)->input);
	free((*g_cmd)->output);
	(*g_cmd)->tokens = NULL;
	(*g_cmd)->input = NULL;
	(*g_cmd)->output = NULL;
}

int		ft_error(t_stock **g_cmd)
{
	char	*err;

	ft_stockclear(g_cmd, clear_one);
	err = ft_strjoin("minishell: ", strerror(errno));
	write(1, err, ft_strlen(err));
	return (0);
}

int		write_error(char *cmd, char *arg, char *err, int error)
{
	g_status = error;
	write(1, "minishell: ", 11);
	write(1, cmd, ft_strlen(cmd));
	write(1, arg, ft_strlen(arg));
	write(1, err, ft_strlen(err));
	return (0);
}
