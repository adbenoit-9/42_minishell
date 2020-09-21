/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/21 13:56:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_stock **cmd_lst, char *envp[])
{
    size_t  size;
    char    *buf;

    size = 0;
    buf = NULL;
    (void)envp;
    (*cmd_lst)->ret = 0;
    getcwd(buf, size);
    return ;
}