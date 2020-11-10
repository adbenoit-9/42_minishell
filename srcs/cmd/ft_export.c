/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/10 18:31:54 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_var(char *str, int *pos)
{
	char	*var;
	int		i;

	var = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!(var = (char *)malloc(sizeof(char) * i + 1)))
	{
		print_errno("export", NULL, MALL_ERR);
		return (NULL);
	}
	i = -1;
	while (str[++i] && str[i] != '=')
		var[i] = str[i];
	var[i] = '\0';
	if (ft_check_var(var) == 0)
	{
		print_error("export: `", str, "\': not a valid identifier\n", 1);
		return (NULL);
	}
	if (str[i] != '=' && str[i] != '\0')
		return (NULL);
	*pos = i;
	return (var);
}

int		ft_add_to_envp(char *envp[], char *str)
{
	int	i;
	int	j;
	int	bool;
	int	size;

	i = 0;
	j = -1;
	bool = 0;
	size = ft_strlen(str) + 1;
	i = ft_tabsize(envp);
	while (str[++j] != 0)
	{
		if (str[j] == '=')
			bool += 1;
	}
	if (bool == 0)
		size += 3;
	if (!(envp[i] = (char *)malloc(sizeof(char) * size)))
		return (-1);
	j = -1;
	while (str[++j] != 0)
		envp[i][j] = str[j];
	if (bool == 0)
	{
		envp[i][j] = '=';
		envp[i][j + 1] = '\'';
		envp[i][j + 2] = '\'';
		j += 3;
	}
	envp[i][j] = 0;
	envp[i + 1] = 0;
	return (0);
}

void	ft_resize_at_pos(char *envp[], char *var, char *new, int pos)
{
	int size;
	int i;
	int j;

	size = ft_strlen(var) + ft_strlen(new) + 1;
	if (!(envp[pos] = ft_realloc(envp[pos], size + 1)))
	{
		print_errno("export", NULL, MALL_ERR);
		return ;
	}
	i = 0;
	j = 0;
	while (var[i] != '\0')
		envp[pos][j++] = var[i++];
	envp[pos][j++] = '=';
	i = 0;
	while (new[i] != '\0')
		envp[pos][j++] = new[i++];
	envp[pos][j] = '\0';
	return ;
}

void	ft_modify_envp(char *envp[], char *var, char *new, int pos)
{
	int i;
	int j;
	int k;
	int l;

	i = ft_strlen(var) + 1;
	j = ft_strlen(new);
	k = 0;
	l = i;
	if (new[0] == '\0' || new == NULL)
		return ;
	while (envp[pos][l] != '\0')
		++l;
	if (l - i == j)
	{
		while (j >= i)
			envp[pos][i++] = new[k++];
		envp[pos][i] = '\0';
	}
	else
		return (ft_resize_at_pos(envp, var, new, pos));
}

void	ft_export(t_stock **cmd, char *envp[], int *fd)
{
	int		pos;
	int		ret;
	int		i;
	char	*var;
	char	*new;
	char	**bis;

	if ((*cmd)->tokens[1] == NULL || !(*cmd)->tokens[1][0])
	{
		bis = ft_tabdup(envp);
		ft_sort_env(bis);
		ft_puttab_fd(bis, fd[1]);
		ft_free(bis);
		return ;
	}
	i = 0;
	while ((*cmd)->tokens[++i])
	{
		if ((var = ft_create_var((*cmd)->tokens[i], &pos)))
		{
			new = ft_strdup((*cmd)->tokens[i] + pos + 1);
			if ((ret = find_var(envp, var)) == -1)
			{
				if ((ft_add_to_envp(envp, (*cmd)->tokens[i])) == -1)
					print_errno("env", NULL, 1);
			}
			else
				ft_modify_envp(envp, var, new, ret);
			free(var);
			free(new);
		}
	}
	return ;
}
