/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:26:19 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 02:04:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char *tab[])
{
	char	**copy;
	size_t	size;
	size_t	i;

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
			ft_freetab(copy);
			return (NULL);
		}
		++i;
	}
	copy[i] = NULL;
	return (copy);
}
