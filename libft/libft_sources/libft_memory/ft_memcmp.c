/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:55:59 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:03 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Compare les n premiers octets des zones mémoire s1 et s2.
** =========
** #1 : la zone mémoire pointée par s1.
** #2 : la zone mémoire pointée par s1.
** #3 : le nombre d'octets à examiner.
** =========
** Retourne un entier inférieur, égal, ou supérieur à zéro,
** si s1 est respectivement inférieure, égale ou supérieur à s2.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*char1;
	unsigned char	*char2;

	i = 0;
	char1 = (unsigned char *)s1;
	char2 = (unsigned char *)s2;
	while ((i < n) && (char1[i] == char2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return (char1[i] - char2[i]);
}
