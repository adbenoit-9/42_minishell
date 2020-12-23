/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:41:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/22 20:39:04 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, int newsize)
{
	void	*newptr;
	int		size;

	if (ptr == 0)
		return (malloc(newsize));
	newptr = malloc(newsize);
	size = ft_strlen(ptr);
	if (newsize > size)
		ft_memcpy(newptr, ptr, newsize);
	else
		ft_memcpy(newptr, ptr, size);
	free(ptr);
	ptr = NULL;
	return (newptr);
}

char	**ft_realloc_tab(char **ptr, int newsize)
{
	char	**newptr;
	int		i;

	i = 0;
	if (ptr == 0)
		return ((char **)malloc(sizeof(char *) * newsize));
	if (!(newptr = (char **)malloc(sizeof(char *) * newsize)))
		return (NULL);
	while (ptr && ptr[i])
	{
		if (!(newptr[i] = ft_strdup(ptr[i])))
			return (NULL);
		free(ptr[i]);
		++i;
	}
	free(ptr);
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
