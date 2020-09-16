/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/16 14:47:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isalphanum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
	|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

void	ft_unset(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int	j;

	i = 0;
	while ((*cmd_lst)->input[i])
	{
		if (ft_isalphanum((*cmd_lst)->input[i]) == 0)
		{
			(*cmd_lst)->output = output_error("unset: `", (*cmd_lst)->input,
			"': not a valid identifier\n");
			if (!((*cmd_lst)->output))
				ft_error(cmd_lst);
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
