/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:00:55 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 13:12:38 by mabriand         ###   ########.fr       */
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
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
		i++;
	}
	if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	if (s1[0] == '\0')
		return ((unsigned char)s1[0] - (unsigned char)s2[0]);
	return (0);
}
