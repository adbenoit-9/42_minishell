/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:35:05 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:21 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"


/*
** Remplit les n premiers octets de la zone mémoire
** pointée par s avec l'octet c.
** =========
** #1 : la zone mémoire pointée.
** #2 : l'octet donné pour le remplissage.
** #3 : le nombre d'octets à remplir. 
** =========
** Retourne un pointeur vers la zone mémoire s.
*/

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			((unsigned char *)b)[i] = (unsigned char)c;
			i++;
		}
	}
	return (b);
}
