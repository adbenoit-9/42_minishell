/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:48:30 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/06 12:54:00 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Copie n octets depuis la zone mémoire src 
** vers la zone mémoire dst.
** Les deux zones peuvent se chevaucher.
** =========
** #1 : la zone mémoire de destination.
** #2 : la zone mémoire source.
** #3 : le nombre d'octets à copier.
** =========
** Retourne un pointeur vers la zone mémoire dst.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (len-- != 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d);
}
