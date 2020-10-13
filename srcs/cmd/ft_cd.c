/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/10 18:37:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(t_stock **cmd_lst, char *envp[])
{
    int     ret;
    char    *str;

    if (ft_redirect(cmd_lst, 0, 0) == -1)
        return ;
    errno = 0;
    ret = chdir((const char *)(*cmd_lst)->input);
    (void)envp;
    //(*cmd_lst)->ret = 0; a voir plus tard
    if (ret == 0)
        return ;
    else
    {
        str = strerror(errno);
        write_error("cd: ", (*cmd_lst)->input[0], ": ");
        write(1, str, ft_strlen(str));
        write(1, "\n" , 1);
    }
}