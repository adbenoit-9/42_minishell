/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/30 19:49:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd, int *fd, char **envp[])
{
	int		pos;
	int		j;

	pos = 0;
	(void)fd;
	while (cmd->tok->next)
	{
		if (check_var_name(cmd->tok->next->content) == 0)
			error_msg("unset: `", cmd->tok->next->content,
			"': not a valid identifier\n", 1);
		if (ft_getenv(cmd->tok->next->content, &pos, *envp))
		{
			free((*envp)[pos]);
			j = pos;
			while ((*envp)[++j])
			{
				(*envp)[pos] = (*envp)[j];
				++pos;
			}
			(*envp)[pos] = 0;
		}
		cmd->tok->next = cmd->tok->next->next;
	}
}
