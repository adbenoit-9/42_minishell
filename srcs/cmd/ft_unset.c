/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 00:23:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **cmd, char *envp[])
{
	int	i;
	int	j;
	int	k;

	if (ft_redirect(cmd, 0, 0) == -1)
        return ;
	k = 0;
	while ((*cmd)->tokens[++k])
	{
		i = 0;
		while ((*cmd)->tokens[k][i])
		{
			if (ft_isalnum((*cmd)->tokens[k][i]) == 0)
			{
				write_error("unset: `", (*cmd)->tokens[k],
			"': not a valid identifier\n", 1);
				break ;
			}
			++i;
		}
		if ((i = find_var(envp, (*cmd)->tokens[k])) != -1)
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
