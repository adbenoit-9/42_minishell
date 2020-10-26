/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/26 20:13:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_stock **cmd_lst, char *envp[])
{
    size_t  size;
    char    *buf;
    char    *str;
    int     fd;

    ft_redirect(cmd_lst, 0, &fd);
    size = 0;
    buf = NULL;
    (void)envp;
    (*cmd_lst)->ret = 0;
    str = getcwd(buf, size);
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    erret = 0;
    return ;
}