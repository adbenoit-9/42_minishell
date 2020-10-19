/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 13:42:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	j;

	i = 0;
	if (ft_redirect(cmd_lst, 0, 0) == -1)
        return ;
	while ((*cmd_lst)->tokens[0] && (*cmd_lst)->tokens[0][i])
	{
		if (ft_isalnum((*cmd_lst)->tokens[0][i]) == 0)
		{
			write_error("unset: `", (*cmd_lst)->tokens[0],
			"': not a valid identifier\n");
			return ;
		}
		++i;
	}
	if ((i = find_var(envp, (*cmd_lst)->tokens[0])) == -1)
		return ;
	j = i;
	while (envp[++j])
	{
		ft_strcpy(envp[i], envp[j]);
		++i;
	}
	envp[i] = 0;
}
