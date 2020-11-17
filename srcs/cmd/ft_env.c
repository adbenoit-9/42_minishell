/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:09 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/17 22:17:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arg_env(t_stock **cmd)
{
	int	ret;

	ret = 0;
	if ((*cmd)->tokens[1] != NULL)
	{
		ret = 1;
		write(2, "env: ", 5);
		write(2, (*cmd)->tokens[1], ft_strlen((*cmd)->tokens[1]));
		write(2, ": No argument required\n", 24);
	}
	return (ret);
}

static int	ft_place(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (1);
		else if (s1[i] > s2[i])
			return (2);
		else
			i++;
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (1);
	if (s1[i] != '\0' && s2[i] == '\0')
		return (2);
	return (0);
}

void		ft_sort_env(char *envp[])
{
	char	*swap;
	int		size;
	int		i;
	int		j;

	swap = NULL;
	size = ft_tabsize(envp);
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_place(envp[j], envp[j + 1]) == 2)
			{
				swap = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = swap;
			}
		}
	}
	return ;
}

void		ft_env(t_stock **cmd, char *envp[], int *fd)
{
	int		index;
	int		i;

	if (ft_arg_env(cmd) == 1)
		return ;
	index = 0;
	while (envp[index])
	{
		i = 0;
		while (envp[index][i])
			++i;
		if (envp[index][i - 1] != '\'' || envp[index][i - 2] != '\'' ||
		envp[index][i - 3] != '=')
		{
			write(fd[1], envp[index], ft_strlen(envp[index]));
			write(fd[1], "\n", 1);
		}
		++index;
	}
	return ;
}
