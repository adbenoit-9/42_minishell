/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 09:58:58 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:59:08 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Copie la chaîne de caractères src dans dst
** jusqu'à dstsize caractères.
** =========
** #1 : une chaîne de caractères de destination.
** #2 : une chaîne de caractères source.
** #3 : le nombre maximal de caractères de dst à ajouter. 
** =========
** Retourne le nombre total de caractères de la chaîne dst
** après copie.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
