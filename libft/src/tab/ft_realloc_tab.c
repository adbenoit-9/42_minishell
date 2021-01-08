/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:29:42 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 02:04:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_tab(char **ptr, size_t newsize)
{
	char	**newptr;
	size_t	i;
	size_t	size;

	if (ptr == 0)
		return ((char **)malloc(sizeof(char *) * newsize));
	size = ft_tabsize(ptr);
	if (size >= newsize)
		return (ptr);
	newptr = (char **)malloc(sizeof(char *) * newsize);
	i = 0;
	while (newptr && i < size)
	{
		if (!(newptr[i] = ft_strdup(ptr[i])))
			break ;
		++i;
	}
	if (i != size)
		newptr = ft_freetab(newptr);
	ptr = ft_freetab(ptr);
	return (newptr);
}
