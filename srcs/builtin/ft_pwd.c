/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/02 15:47:13 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd, int *fd, char **envp[])
{
	size_t	size;
	char	*buf;
	char	*str;
	int		n;

	size = 0;
	buf = NULL;
	if (!(str = getcwd(buf, size)))
		if (!(str = ft_getenv("PWD", &n, *envp)))
			if (!(str = g_shell.pwd))
				return ;
	str = ft_correct_path(str);
	ft_putstr_fd(str, fd[1]);
	free(str);
	write(fd[1], "\n", 1);
	(void)fd;
	cmd->err = NONE;
	return ;
}
