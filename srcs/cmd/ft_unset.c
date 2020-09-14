/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/14 18:04:02 by adbenoit         ###   ########.fr       */
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
		if ((*cmd_lst)->input[i] == '=')
		{
			(*cmd_lst)->output = output_error("unset: `", (*cmd_lst)->input,
			"': not a valid identifier\n");
			if (!((*cmd_lst)->output))
				ft_error(cmd_lst);
			return ;
		}
		++i;
	}
	i = find_var(envp, (*cmd_lst)->input);
	j = i;
	while (envp[++j])
	{
		ft_strcpy(envp[i], envp[j]);
		++i;
	}
	envp[i] = 0;
}
