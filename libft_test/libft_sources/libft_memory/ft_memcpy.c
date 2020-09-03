/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:39:11 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:05 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Copie n octets depuis la zone mémoire src 
** vers la zone mémoire dst.
** Les deux zones ne doivent pas se chevaucher.
** (Si c'est le cas, utilisez plutôt memmove(3)).
** =========
** #1 : la zone mémoire de destination.
** #2 : la zone mémoire source.
** #3 : le nombre d'octets à copier.
** =========
** Retourne un pointeur vers la zone mémoire dst.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (char *)dst;
	s = (const char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
