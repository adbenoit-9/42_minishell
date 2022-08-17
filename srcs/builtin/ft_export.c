/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:45:38 by adbenoit          #+#    #+#             */
/*   Updated: 2022/08/17 13:50:10 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_var_name(char *name, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '+' && str[i] != '=')
		++i;
	name = ft_strncpy(name, str, i);
	name[i] = 0;
	return (name);
}

static void	ft_display(char *str, int fd)
{
	int		i;
	int		j;
	char	new[4096];

	if (!str || !str[0])
		return ;
	i = 0;
	j = 0;
	ft_putstr_fd("=\"", fd);
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\\' || str[i] == '$' || str[i] == '`')
		{
			new[j] = '\\';
			++j;
		}
		new[j] = str[i];
		++j;
	}
	new[j] = 0;
	ft_putstr_fd(new, fd);
	ft_putchar_fd('\"', fd);
}

static void	ft_putexp_fd(t_list *ptr, int fd, char *envp[])
{
	char	**copy;
	char	var[4096];
	int		i;
	int		len;

	if (!ptr)
	{
		if (!(copy = ft_tabdup(envp)))
		{
			errno_msg(NULL, NULL, MALL_ERR);
			return ;
		}
		ft_sortenv(copy);
		i = -1;
		while (copy[++i])
		{
			get_var_name(var, copy[i]);
			len = ft_strlen(var);
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(var, fd);
			ft_display(copy[i] + len, fd);
			ft_putchar_fd('\n', fd);
		}
		ft_freetab(copy);
	}
}

static int	ft_putname_only(char *name, char **envp[])
{
	int	len;

	len = ft_tabsize(*envp);
	*envp = ft_realloc_tab(*envp, len + 2);
	if (!*envp || !((*envp)[len] = strdup(name)))
	{
		errno_msg(NULL, NULL, MALL_ERR);
		return (-1);
	}
	(*envp)[len + 1] = 0;
	return (0);
}

void		ft_export(t_cmd *cmd, int *fd, char **envp[])
{
	int		len;
	char	var[4096];
	t_list	*tmp;

	tmp = cmd->tok->next;
	while (tmp)
	{
		get_var_name(var, tmp->content);
		len = ft_strlen(var);
		if (check_var_name(var) == 0)
			error_msg("export: `", tmp->content,
			"\': not a valid identifier\n", 1);
		else if (tmp->content[len] == '+' && tmp->content[len + 1] == '=')
			ft_setenv(var, tmp->content + len + 2, 1, envp);
		else if (tmp->content[len] == '=')
			ft_setenv(var, tmp->content + len + 1, 0, envp);
		else if (!tmp->content[len] && !ft_getenv(tmp->content, 0, *envp))
			ft_putname_only(var, envp);
		tmp = tmp->next;
	}
	ft_putexp_fd(cmd->tok->next, fd[1], *envp);
}
