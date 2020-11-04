/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/04 18:53:53 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	j;
	int	k;

	if (ft_redirect(cmd_lst, 0, 0) == -1)
        return ;
	k = 0;
	while ((*cmd_lst)->tokens[++k])
	{
		i = 0;
		while ((*cmd_lst)->tokens[k][i])
		{
			if (ft_isalnum((*cmd_lst)->tokens[k][i]) == 0)
			{
				write_error("unset: `", (*cmd_lst)->tokens[k],
			"': not a valid identifier\n", 1);
				break ;
			}
			++i;
		}
		if ((i = find_var(envp, (*cmd_lst)->tokens[k])) != -1)
		{
			j = i;
			while (envp[++j])
			{
				ft_strcpy(envp[i], envp[j]);
				++i;
			}
			envp[i] = 0;
		}
	}
}
