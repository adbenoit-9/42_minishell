/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 21:09:04 by adbenoit         ###   ########.fr       */
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
	n = 0;
	(void)envp;
	if (!(str = getcwd(buf, size)))
	{
		if (!(str = g_shell.pwd))
			return ;
		n = 1;
	}
	if (n == 0)
		str = ft_correct_path(str);
	ft_putstr_fd(str, fd[1]);
	if (n == 0)
		free(str);
	write(fd[1], "\n", 1);
	cmd->err = NONE;
	return ;
}
