/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/15 17:19:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_one(t_stock **cmd_lst)
{
	free((*cmd_lst)->output);
	free((*cmd_lst)->input);
	(*cmd_lst)->output = NULL;
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

char	*output_error(char *cmd, char *arg, char *err)
{
	char	*output;
	char	*new;

	cmd = ft_strjoin(cmd, arg);
	new = ft_strjoin("minishell: ", cmd);
	free(cmd);
	output = ft_strjoin(new, err);
	free(new);
	return (output);
}
