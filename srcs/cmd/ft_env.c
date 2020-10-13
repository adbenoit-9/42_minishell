
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/10 17:45:22 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_arg_env(t_stock **cmd_lst)
{
    int     ret;

    ret = 0;
    if ((*cmd_lst)->input[0] != '\0')
    {
        ret = 1;
        write_error("env: ", (*cmd_lst)->input[0], ": error (argument management for 'env' not required)\n");
    }
    return (ret);
}


void    ft_env(t_stock **cmd_lst, char *envp[])
{
    char    *str;
    char    *new;
    int     index;
    int     fd;

    str = NULL;
    new = NULL;
    index = 0;
    //(*cmd_lst)->ret = 0; ????????????????
    if ((fd = ft_redirect(cmd_lst, &fd, 0)) == -1)
        return ;
    if (ft_arg_env(cmd_lst) == 1)
        return ;
    while (envp[index])
    {
        if (str == NULL)
        {
            str = ft_strdup(envp[index]);
            index++;
        }
        new = ft_strjoin(str, "\n");
        free(str);
        str = ft_strjoin(new, envp[index]);
        free(new);
        index++;
    }
    new = ft_strjoin(str, "\n");
    free(str);
    write(fd, new, ft_strlen(new));
    free(new);
    return ;
}