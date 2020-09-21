/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/21 13:51:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	j;

	i = 0;
	while ((*cmd_lst)->input[i])
	{
		if (ft_isalnum((*cmd_lst)->input[i]) == 0)
		{
			write_error("unset: `", (*cmd_lst)->input,
			"': not a valid identifier\n");
			return ;
		}
		++i;
	}
	if ((i = find_var(envp, (*cmd_lst)->input)) == -1)
		return ;
	j = i;
	while (envp[++j])
	{
		ft_strcpy(envp[i], envp[j]);
		++i;
	}
	envp[i] = 0;
}
