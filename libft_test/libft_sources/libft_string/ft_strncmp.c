/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:00:55 by mabriand          #+#    #+#             */
/*   Updated: 2020/09/04 00:44:42 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Compare les n (au plus) premiers caractères 
** de deux chaînes s1 et s2.
** =========
** #1 : une chaîne de caractères s1.
** #2 : une chaîne de caractères s2.
** #3 : le nombre maximal de caractères à comparer. 
** =========
** Retourne un entier négatif, nul, ou positif,
** si s1 est respectivement inférieure, égale ou supérieure à s2.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
