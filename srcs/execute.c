/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:13:08 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/29 22:39:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute(t_list **cmd_lst)
{
    t_function	cmd_fct[NUM_CMD] = {ft_echo, ft_cd, ft_pwd, ft_env,
									ft_export, ft_unset, ft_exit};
    int			i;

    i = 0;
    while (*cmd_lst && i < NUM_CMD && (*cmd_lst)->cmd != i)
        ++i;
    if (i == NUM_CMD)
        ft_error(NULL);
    if (*cmd_lst && (*cmd_lst)->cmd != UNKNOW)
        cmd_fct[i](cmd_lst);
}
