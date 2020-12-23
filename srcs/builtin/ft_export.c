/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 01:50:00 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_create_var(char *str, int *pos)
{
	char	*var;
	int		i;

	var = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(var = (char *)malloc(sizeof(char) * i + 1)))
	{
		errno_msg("export", NULL, MALL_ERR);
		return (NULL);
	}
	i = -1;
	while (str[++i] && str[i] != '=')
		var[i] = str[i];
	var[i] = '\0';
	if (check_var_name(var) == 0)
	{
		error_msg("export: `", str, "\': not a valid identifier\n", 1);
		return (NULL);
	}
	if (str[i] != '=' && str[i] != '\0')
		return (NULL);
	*pos = i;
	return (var);
}

int			ft_add_to_env(char *str)
{
	int	i;
	int	j;
	int	bool;
	int	size;

	bool = 0;
	size = ft_strlen(str) + 1;
	size = size > 4098 ? size : 4098;
	i = ft_tabsize(envp);
	j = -1;
	while (str[++j] != 0)
	{
		if (str[j] == '=' && str[j + 1])
			bool = 1;
	}
	if (!(envp[i] = (char *)malloc(sizeof(char) * size)))
		return (errno_msg(NULL, NULL, MALL_ERR));
	ft_strcpy(envp[i], str);
	if (bool == 0 && str[j - 1] != '=')
		ft_strcpy(envp[i] + j, "=\'\'");
	envp[i + 1] = 0;
	return (0);
}

void		ft_modify_envp(char *var, char *new, int pos)
{
	if (new[0] == '\0' || new == NULL)
		return ;
	ft_strcpy(envp[pos] + ft_strlen(var) + 1, new);
}

static void	ft_none_arg(char *token, int *fd, char *envp[])
{
	char	**copy;
	int		i;
	int		j;

	if (!token)
	{
		copy = ft_tabdup(envp);
		ft_sort_env(copy);
		i = -1;
		while (copy[++i])
		{
			write(fd[1], copy[i], ft_strlen(copy[i]));
			j = 0;
			while (copy[i][j] && copy[i][j] != '=')
				++j;
			if (copy[i][j] && !copy[i][j + 1])
				write(fd[1], "\'\'", 2);
			write(fd[1], "\n", 1);
		}
		ft_free(copy);
		return ;
	}
	error_msg("export: `", token, "\': not a valid identifier\n", 1);
}

void		ft_export(t_cmd **cmd, int *fd)
{
	int		pos;
	int		i;
	char	*var;
	char	*new;

	if ((*cmd)->tokens[1] == NULL || !(*cmd)->tokens[1][0])
		return (ft_none_arg((*cmd)->tokens[1], fd));
	i = 0;
	while ((*cmd)->tokens[++i])
	{
		if ((var = ft_create_var((*cmd)->tokens[i], &pos)))
		{
			new = ft_strdup((*cmd)->tokens[i] + pos + 1);
			if ((pos = ft_getpos(var)) == -1)
			{
				if ((ft_add_to_env((*cmd)->tokens[i])) == -1)
					errno_msg("env", NULL, MALL_ERR);
			}
			else
				ft_modify_env(var, new, pos);
			free(var);
			free(new);
		}
	}
	return ;
}
