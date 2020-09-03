/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:50:28 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:02 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Examine les n premiers octets de la zone mémoire
** pointée par s à la recherche du caractère c.
** Le premier octet correspondant à c (interprété comme
** unsigned char) arrête l'opération.
** =========
** #1 : la zone mémoire pointée.
** #2 : le caractère à rechercher.
** #3 : le nombre d'octets à examiner.
** =========
** Retourne un pointeur vers l'octet correspondant
** ou NULL s'il n'est pas présent dans la zone concernée.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		c2;
	unsigned char		*str;

	i = 0;
	c2 = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == c2)
		{
			return ((void *)(str + i));
		}
		i++;
	}
	return (NULL);
}
