
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
    if ((*cmd_lst)->tokens[1] != NULL)
    {
        ret = 1;
        write_error("env: ", (*cmd_lst)->tokens[1], ": error (argument management for 'env' not required)\n", 1);
    }
    return (ret);
}

int     ft_place(char *s1, char *s2)
{  
    int i;
    
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] < s2[i])
            return (1);
        else if (s1[i] > s2[i])
            return (2);
        else
            i++;
    }
    if (s1[i] == '\0' && s2[i] != '\0')
        return (1);
    if (s1[i] != '\0' && s2[i] == '\0')
        return (2);
    return (0);
}

char    **ft_copy_tab(char *envp[])
{
    char    **bis;
    int     size;
    int     i;

    bis = NULL;
    size = 0;
    i = 0;
    while (envp[size])
        size++;
    if(!(bis = malloc(sizeof(char *) * (size + 1))))
        return (NULL);
    while (i < size)
    {
        bis[i] = ft_strdup(envp[i]);
        //write(1, bis[i], ft_strlen(bis[i]));
        //write(1, "\n", 1);
        i++;
    }
    bis[i] = NULL;
    return (bis);
}

void    ft_sort_env(char *envp[])
{
    char    *swap;
    int     size;
    int     i;
    int     j;

    swap = NULL;
    size = 0;
    while (envp[size] != 0)
        size++;
        
    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (ft_place(envp[j], envp[j + 1]) == 2)
            {
                swap = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = swap;
            }
            j++;
        }
        i++;
    }
    return ;
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
        int i = 0;
        while (envp[index][i])
            ++i;
        if (envp[index][i - 1] == '\'' && envp[index][i - 2] == '\'' && envp[index][i - 3] == '=')
            index++;
        else
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
    }
    new = ft_strjoin(str, "\n");
    free(str);
    write(fd, new, ft_strlen(new));
    free(new);
    return ;
}