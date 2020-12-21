/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:50:40 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:10:10 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Concatène la chaîne de caractères src à la fin de dst,
** en veillant à ce que le nombre de cartères de dst après
** concaténation ne dépasse pas dstsize.
** =========
** #1 : une chaîne de caractères de destination.
** #2 : une chaîne de caractères source.
** #3 : le nombre maximal de caractères de dst à ajouter.
** =========
** Retourne le nombre total de caractères de la chaîne dst
** avant concaténation auquel on ajoute celui de src.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t len;
	size_t lensrc;
	size_t lendest;
	size_t j;

	lensrc = ft_strlen(src);
	lendest = ft_strlen(dst);
	j = 0;
	if (dstsize <= lendest)
		len = lensrc + dstsize;
	else
		len = lensrc + lendest;
	if (dstsize > lendest)
	{
		while (src[j] != '\0' && lendest < dstsize - 1)
		{
			dst[lendest] = src[j];
			lendest++;
			j++;
		}
		dst[lendest] = '\0';
	}
	return (len);
}
