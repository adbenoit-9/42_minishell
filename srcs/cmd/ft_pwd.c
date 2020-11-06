/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:33:44 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_stock **g_cmd, char *envp[])
{
    size_t  size;
    char    *buf;
    char    *str;
    int     fd;

    fd = 1;
    ft_redirect(g_cmd, 0, &fd);
    size = 0;
    buf = NULL;
    str = getcwd(buf, size);
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    g_status = 0;
    (void)envp;
    return ;
}