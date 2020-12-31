/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:41:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/31 01:03:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *ptr, int newsize)
{
	char	*newptr;
	int		size;

	if (ptr == 0)
		return (malloc(newsize));
	size = ft_strlen((char *)ptr);
	if (newsize <= size)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(newptr, ptr, size);
	free(ptr);
	ptr = NULL;
	return (newptr);
}

char	**ft_realloc_tab(char **ptr, int newsize)
{
	char	**newptr;
	int		i;
	int		size;

	i = 0;
	if (ptr == 0)
		return ((char **)malloc(sizeof(char *) * newsize));
	size = ft_tabsize(ptr);
	if (size >= newsize)
		return (ptr);
	newptr = (char **)malloc(sizeof(char *) * newsize);
	while (i < size)
	{
		if (!(newptr[i] = ft_strdup(ptr[i])))
			break ;
		++i;
	}
	if (i != size)
	{
		ft_free(newptr);
		newptr = NULL;
	}
	ft_free(ptr);
	ptr = NULL;
	return (newptr);
}

void	*ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
