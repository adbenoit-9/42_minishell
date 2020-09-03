/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:57:14 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/05 12:21:06 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Depuis une chaîne de caractères s1, en crée une nouvelle
** dont la mémoire occupée est obtenue par un appel de malloc(3).
** =======
** #1 : chaîne à dupliquer.
** =======
** Retourne un pointeur sur la chaîne dupliquée depuis s1,
** ou NULL s'il l'allocation dynamique de mémoire échoue.
*/

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;
	size_t	size;
	char	*copy;

	i = 0;
	s = (char *)s1;
	size = ft_strlen(s);
	copy = ((char *)malloc(sizeof(*copy) * (size + 1)));
	if (copy == NULL)
		return (NULL);
	while (i < size)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
