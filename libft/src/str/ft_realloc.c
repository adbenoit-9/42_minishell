/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:41:55 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 01:37:07 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t newsize)
{
	char	*newptr;
	size_t	size;

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
