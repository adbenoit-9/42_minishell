/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:49:15 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:06:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Alloue (avec malloc(3)) la mémoire nécessaire pour un tableau
** de count éléments de taile size octets.
** =======
** #1 : nombre d'éléments dans le tableau.
** #2 : taille en octets d'un élément.
** =======
** Retourne un pointeur sur l méoire allouée,
** NULL si count ou size vaut 0.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(size * count);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, size * count);
	return (mem);
}
