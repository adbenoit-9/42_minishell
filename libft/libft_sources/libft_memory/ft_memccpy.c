/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:43:20 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:11:36 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Copie au plus n octets de la zone mémoire src
** vers la zone mémoire dst, s'arrêtant dès qu'elle
** rencontre le caractère c.
** =========
** #1 : la chaîne de destination.
** #2 : la chaîne source.
** #3 : le caractère à chercher.
** #4 : le nombre maximal d'octets à copier.
** =========
** Retourne un pointeur sur le caractère
** immédiatement après c dans dst, NULL si c n'a pas été trouvé
** dans les n premiers caractères de src.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*p;

	p = ft_memchr(src, c, n);
	if (p == NULL)
	{
		ft_memcpy(dst, src, n);
		return (NULL);
	}
	ft_memcpy(dst, src, p - src + 1);
	return (dst + (p - src + 1));
}
