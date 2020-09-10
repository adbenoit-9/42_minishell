/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:27:30 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/10 18:14:05 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(t_stock **cmd_lst, char *envp[])
{
    int     ret;
    char    *str;
    char    *new;

    errno = 0;
    ret = chdir((const char *)(*cmd_lst)->input);
    str = NULL;
    (void)envp;
    //(*cmd_lst)->ret = 0; a voir plus tard
    if (ret == 0)
        return ;
    else
    {
        str = strdup("cd: ");
        new = ft_strjoin(str, strerror(errno));
        new[ft_strlen(new) - 1] = '\0';
        free(str);
        str = ft_strjoin(new, ": ");
        free(new);
        new = ft_strjoin(str, (*cmd_lst)->input);
        free(str);
        (*cmd_lst)->output = new;
        // new final (passé à (*cmd_lst)->output) à FREE à la fin
    }
}