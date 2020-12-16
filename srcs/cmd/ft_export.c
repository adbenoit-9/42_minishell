/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/16 21:06:51 by adbenoit         ###   ########.fr       */
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
	if (ft_check_var(var) == 0)
	{
		error_msg("export: `", str, "\': not a valid identifier\n", 1);
		return (NULL);
	}
	if (str[i] != '=' && str[i] != '\0')
		return (NULL);
	*pos = i;
	return (var);
}

int	ft_add_to_envp(char *envp[], char *str)
{
	int	i;
	int	j;
	int	bool;
	int	size;

	bool = 0;
	size = ft_strlen(str) + 1;
	i = ft_tabsize(envp);
	j = -1;
	while (str[++j] != 0)
	{
		if (str[j] == '=' && str[j + 1])
			bool = 1;
	}
	if (bool == 0)
		size = (str[j - 1] != '=') ? size + 3 : size + 2;
	if (!(envp[i] = (char *)malloc(sizeof(char) * size)))
		return (-1);
	ft_strcpy(envp[i], str);
	j = (str[j - 1] == '=') ? j - 1 : j;
	if (bool == 0)
		ft_strcpy(envp[i] + j, "=\'\'");
	envp[i + 1] = 0;
	return (0);
}

void	ft_modify_envp(char *envp[], char *var, char *new, int pos)
{
	if (new[0] == '\0' || new == NULL)
		return ;
	// printf("envp[%d] = %s\n", pos, envp[pos]);
	ft_strcpy(envp[pos] + ft_strlen(var) + 1, new);
}

static void	ft_none_arg(char *token, char *envp[], int *fd)
{
	char	**copy;

	if (!token)
	{
		copy = ft_tabdup(envp);
		ft_sort_env(copy);
		ft_puttab_fd(copy, fd[1]);
		ft_free(copy);
		return ;
	}
	error_msg("export: ", "not valid in this context:", token, 1);
	write(2, "\n", 1);
}

void		ft_export(t_stock **cmd, char *envp[], int *fd)
{
	int		pos;
	int		i;
	char	*var;
	char	*new;

	if ((*cmd)->tokens[1] == NULL || !(*cmd)->tokens[1][0])
		return (ft_none_arg((*cmd)->tokens[1], envp, fd));
	i = 0;
	while ((*cmd)->tokens[++i])
	{
		if ((var = ft_create_var((*cmd)->tokens[i], &pos)))
		{
			new = ft_strdup((*cmd)->tokens[i] + pos + 1);
			if ((pos = find_var(envp, var)) == -1)
			{
				if ((ft_add_to_envp(envp, (*cmd)->tokens[i])) == -1)
					errno_msg("env", NULL, MALL_ERR);
			}
			else
				ft_modify_envp(envp, var, new, pos);
			free(var);
			free(new);
		}
	}
	return ;
}
