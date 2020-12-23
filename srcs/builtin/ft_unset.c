/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 01:56:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd **cmd, int *fd, char *envp[])
{
	int	pos;
	int	j;
	int	k;

	k = 0;
	pos = 0;
	(void)fd;
	while ((*cmd)->tokens[++k])
	{
		if (check_var_name((*cmd)->tokens[k]) == 0)
		{
			error_msg("unset: `", (*cmd)->tokens[k],
			"': not a valid identifier\n", 1);
		}
		if (ft_getenv((*cmd)->tokens[k], &pos, envp))
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
