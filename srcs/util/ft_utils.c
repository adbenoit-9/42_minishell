/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:18:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/23 03:24:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		++i;
	return (i);
}

char	**ft_tabdup(char *tab[])
{
	char	**copy;
	int		size;
	int		i;

	copy = NULL;
	size = 0;
	i = 0;
	size = ft_tabsize(tab);
	if (!(copy = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ft_puttab_fd(char **tab, int fd)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		write(fd, tab[i], ft_strlen(tab[i]));
		write(fd, "\n", 1);
		++i;
	}
	return ;
}

int		check_var_name(char *var)
{
	int i;

	if (!var)
		return (1);
	if (!var[0])
		return (0);
	if (var[0] && ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (0);
	i = -1;
	while (var[++i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}
