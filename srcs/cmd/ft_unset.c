/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/08 23:17:28 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **cmd, char *envp[])
{
	int	pos;
	int	j;
	int	k;

	if (ft_redirect(cmd, 0, 0) == -1)
        return ;
	k = 0;
	while ((*cmd)->tokens[++k])
	{
		if (ft_check_var((*cmd)->tokens[k]) == 0)
		{
			print_error("unset: `", (*cmd)->tokens[k],
			"': not a valid identifier\n", 1);
		}
		if ((pos = find_var(envp, (*cmd)->tokens[k])) != -1)
		{
			j = pos;
			while (envp[++j])
			{
				ft_strcpy(envp[pos], envp[j]);
				++pos;
			}
			envp[pos] = 0;
		}
	}
}
