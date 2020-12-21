/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:41:55 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/21 03:58:58 by adbenoit         ###   ########.fr       */
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
	if (!(newptr = (char **)malloc(sizeof(char *) * newsize)))
		return (NULL);
	while (ptr && ptr[i])
	{
		if (!(newptr[i] = (char *)ft_realloc(ptr[i], ft_strlen(ptr[i]) + 1)))
			return (NULL);
		++i;
	}
	newptr[i++] = 0;
	newptr[i] = 0;
	if (ptr != 0)
		free(ptr);
	ptr = NULL;
	return (newptr);
}

double	**realloc_doub(double **ptr, int newsize)
{
	double	**newptr;
	int		i;

	i = 0;
	if (!(newptr = malloc(sizeof(double *) * newsize)))
		return (NULL);
	while (i < newsize - 1)
	{
		if (!(newptr[i] = (double *)ft_realloc(ptr[i], sizeof(double) * 2)))
			return (NULL);
		i++;
	}
	if (!(newptr[i] = (double *)malloc(sizeof(double) * 2)))
		return (NULL);
	if (ptr != 0)
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
