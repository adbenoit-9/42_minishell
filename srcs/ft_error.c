/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:02:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 14:00:45 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *cmd, char *arg, char *err, int error)
{
	g_status = error;
	write(1, "minishell: ", 11);
	if (cmd)
		write(1, cmd, ft_strlen(cmd));
	if (arg)
		write(1, arg, ft_strlen(arg));
	if (err)
		write(1, err, ft_strlen(err));
	return (0);
}

int	print_errno(char *cmd, char *str, int ret)
{
	char	*str_errno;

	g_status = 1;
	write(1, "minishell: ", 11);
	if (cmd)
	{
		write(1, cmd, ft_strlen(cmd));
		write(1, ": ", 2);
	}
	if (str)
	{
		write(1, str, ft_strlen(str));
		write(1, ": ", 2);
	}
	str_errno = strerror(errno);
	write(1, str_errno, ft_strlen(str_errno));
	write(1, "\n", 1);
	return (ret);
}
