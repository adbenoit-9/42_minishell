/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/11 17:17:15 by adbenoit         ###   ########.fr       */
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
	while ((*cmd_lst)->input[0] && (*cmd_lst)->input[0][i])
	{
		if (ft_isalnum((*cmd_lst)->input[0][i]) == 0)
		{
			write_error("unset: `", (*cmd_lst)->input[0],
			"': not a valid identifier\n");
			return ;
		}
		++i;
	}
	if ((i = find_var(envp, (*cmd_lst)->input[0])) == -1)
		return ;
	j = i;
	while (envp[++j])
	{
		ft_strcpy(envp[i], envp[j]);
		++i;
	}
	envp[i] = 0;
}
