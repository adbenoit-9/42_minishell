/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:18:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/30 17:57:42 by adbenoit         ###   ########.fr       */
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
		if (!(copy[i] = ft_strdup(tab[i])))
		{
			ft_free(copy);
			return (NULL);
		}
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

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	if (!src || !dest)
		return (dest);
	i = 0;
	while (dest[i])
		++i;
	j = -1;
	while (src[++j])
	{
		dest[i] = src[j];
		++i;
	}
	dest[i] = 0;
	return (dest);
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
