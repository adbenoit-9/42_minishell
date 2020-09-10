
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
    char    *str;
    char    *new;

    ret = 0;
    str = NULL;
    new = NULL;
    if ((*cmd_lst)->input[0] != '\0')
    {
        ret = 1;
        str = strdup("env: ");
        new = ft_strjoin(str, (*cmd_lst)->input);
        free(str);
        str = ft_strjoin(new, ": error (argument management for 'env' not required)\n");
        free(new);
        (*cmd_lst)->output = str;
        // str final (passé à (*cmd_lst)->output) à FREE à la fin
        // (donc pas dans cette fonction forcément mais ici il y a forcément un LEAK!

        //(*cmd_lst)->ret = 1; ça pour le moment on sait pas trop pk l'utiliser
    }
    return (ret);
}


void    ft_env(t_stock **cmd_lst, char *envp[])
{
    char    *str;
    char    *new;
    int     index;

    str = NULL;
    new = NULL;
    index = 0;
    //(*cmd_lst)->ret = 0; ????????????????
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
    (*cmd_lst)->output = new;
    // new final (passé à (*cmd_lst)->output) à FREE à la fin
    // (donc pas dans cette fonction forcément mais ici il y a forcément un LEAK!
    return ;
}