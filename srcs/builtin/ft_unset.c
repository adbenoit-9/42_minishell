/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/24 02:13:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd, int *fd, char *envp[])
{
	int		pos;
	int		j;
	t_list	*tmp;

	pos = 0;
	(void)fd;
	tmp = cmd->tok->next;
	while (tmp)
	{
		if (check_var_name(tmp->content) == 0)
		{
			error_msg("unset: `", tmp->content,
			"': not a valid identifier\n", 1);
		}
		if (ft_getenv(tmp->content, &pos, envp))
		{
			free(envp[pos]);
			j = pos;
			while (envp[++j])
			{
				envp[pos] = envp[j];
				++pos;
			}
			envp[pos] = 0;
		}
		tmp = tmp->next;
	}
}
