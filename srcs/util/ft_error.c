/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/31 01:53:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *cmd, char *arg, char *err, int error)
{
	g_status = error;
	write(2, "minishell: ", 11);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (err)
		write(2, err, ft_strlen(err));
	return (error);
}

int	errno_msg(char *cmd, char *str, int ret)
{
	char	*str_errno;

	g_status = 1;
	if (ret == MALL_ERR)
		errno = ENOMEM;
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	str_errno = strerror(errno);
	write(2, str_errno, ft_strlen(str_errno));
	write(2, "\n", 1);
	return (ret);
}
