/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:41:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/10 16:20:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, int newsize)
{
	void	*newptr;

	if (ptr == 0)
		return (malloc(newsize));
	newptr = malloc(newsize);
	ft_memcpy(newptr, ptr, newsize);
	free(ptr);
	ptr = NULL;
	return (newptr);
}

char	**realloc_tab(char **ptr, int newsize)
{
	char	**newptr;
	int		i;

	i = 0;
	if (!(newptr = malloc(sizeof(char *) * newsize)))
		return (NULL);
	while (i < newsize - 2)
	{
		if (!(newptr[i] = (char *)ft_realloc(ptr[i], ft_strlen(ptr[i]) + 1)))
			return (NULL);
		i++;
	}
	newptr[i + 1] = 0;
	if (ptr != 0)
		free(ptr);
	ptr = NULL;
	return (newptr);
}
