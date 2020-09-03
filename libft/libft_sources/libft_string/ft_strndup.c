/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:13:43 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/12 14:46:38 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Alloue avec malloc (3) un emplacement mémoire
** dans lequelle elle copie les n premiers caractères de s1.
** =========
** #1 : une chaîne de caractères à dupliquer.
** #2 : la taille de la partie à dupliquer.
** =========
** Retourne un pointeur sur la chaîne dupliquée depuis s1,
** ou NULL s'il l'allocation dynamique de mémoire échoue.
*/

char		*ft_strndup(char *s1, size_t size)
{
	size_t	i;
	char	*copy;

	i = 0;
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
