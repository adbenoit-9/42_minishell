/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 19:16:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_stock **g_cmd, char *envp[])
{
	int	i;
	int	j;
	int	k;

	if (ft_redirect(g_cmd, 0, 0) == -1)
        return ;
	k = 0;
	while ((*g_cmd)->tokens[++k])
	{
		i = 0;
		while ((*g_cmd)->tokens[k][i])
		{
			if (ft_isalnum((*g_cmd)->tokens[k][i]) == 0)
			{
				write_error("unset: `", (*g_cmd)->tokens[k],
			"': not a valid identifier\n", 1);
				break ;
			}
			++i;
		}
		if ((i = find_var(envp, (*g_cmd)->tokens[k])) != -1)
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
