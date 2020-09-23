/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/23 16:54:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_stock **cmd_lst, char *envp[])
{
    size_t  size;
    char    *buf;
    char    *str;
    int     fd;

    if (ft_redirect(cmd_lst, &fd, 0) == -1)
        return ;
    size = 0;
    buf = NULL;
    (void)envp;
    (*cmd_lst)->ret = 0;
    str = getcwd(buf, size);
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    return ;
}