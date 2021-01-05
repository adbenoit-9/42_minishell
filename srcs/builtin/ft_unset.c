/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 17:49:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unsetenv(char *name, char **envp[])
{
	int		n;
	int		i;
	char	*value;

	n = 0;
	if ((value = ft_getenv(name, &n, *envp)))
	{
		if (ft_strcmp(name, "PWD") == 0)
		{
			free(g_shell.pwd);
			g_shell.pwd = ft_strdup(value);
		}
		free((*envp)[n]);
		i = n;
		while ((*envp)[++i])
		{
			(*envp)[n] = (*envp)[i];
			++n;
		}
		(*envp)[n] = 0;
		return (0);
	}
	return (-1);
}

void		ft_unset(t_cmd *cmd, int *fd, char **envp[])
{
	t_list	*tmp;

	(void)fd;
	(void)envp;
	tmp = cmd->tok->next;
	while (tmp)
	{
		if (check_var_name(tmp->content) == 0)
			error_msg("unset: `", tmp->content,
			"': not a valid identifier\n", 1);
		ft_unsetenv(tmp->content, envp);
		tmp = tmp->next;
	}
}
