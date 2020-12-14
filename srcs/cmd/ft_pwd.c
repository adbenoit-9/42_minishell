/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/12 15:27:58 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_stock **cmd, char *envp[], int *fd)
{
	size_t	size;
	char	*buf;
	char	*str;

	size = 0;
	buf = NULL;
	str = getcwd(buf, size);
	if (ft_strcmp(str, "/private/tmp") == 0 && g_tmp == 1)
		write(fd[1], "/tmp", 4);
	else if (ft_strcmp(str, "/private/tmp") == 0 && g_tmp == 2)
		write(fd[1], "//tmp", 5);
	else if (ft_strcmp(str, "/private") == 0 && g_tmp == 1)
		write(fd[1], "/", 1);
	else if ((ft_strcmp(str, "/private") == 0
			|| ft_strcmp(str, "/private/tmp") != 0) && g_tmp == 2)
		write(fd[1], "//", 2);
	else
		write(fd[1], str, ft_strlen(str));
	write(fd[1], "\n", 1);
	(void)envp;
	(void)fd;
	(*cmd)->err = NONE;
	return ;
}
