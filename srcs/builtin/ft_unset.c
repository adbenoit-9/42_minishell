/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/02 15:46:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd, int *fd, char **envp[])
{
	int		pos;
	char	*value;
	int		j;

	pos = 0;
	(void)fd;
	while (cmd->tok->next)
	{
		if (check_var_name(cmd->tok->next->content) == 0)
			error_msg("unset: `", cmd->tok->next->content,
			"': not a valid identifier\n", 1);
		if ((value = ft_getenv(cmd->tok->next->content, &pos, *envp)))
		{
			if (ft_strcmp(cmd->tok->next->content, "PWD") == 0)
			{
				free(g_shell.pwd);
				g_shell.pwd = ft_strdup(value);
			}
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
