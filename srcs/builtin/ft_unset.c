/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:01:45 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 20:54:33 by adbenoit         ###   ########.fr       */
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
