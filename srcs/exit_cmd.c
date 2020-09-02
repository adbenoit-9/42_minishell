/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:47:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/02 17:14:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit(t_list **cmd_lst)
{
    // int value;
    int i;

    i = 0;
    write(1, "exit\n", 5);
    while ((*cmd_lst)->input[i] && (*cmd_lst)->input[i] != '\n')
    {
        if (((*cmd_lst)->input[i] < '0' || (*cmd_lst)->input[i] > '9') && (*cmd_lst)->input[0] != '-')
        {
            write(1, "bash: exit: ", 12);
            write(1, (*cmd_lst)->input, ft_strlen((*cmd_lst)->input) - 1);
            write(1, ": numeric argument required\n", 28);
            break ;
        }
        ++i;
    }
    // value = atoi((*cmd_lst)->input);
    exit(EXIT_SUCCESS);
}