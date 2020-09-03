/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:59:24 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 13:05:00 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Alloue (avec malloc(3)) et retourne une copie de
** la chaine s1, sans les caractères spécifiés
** dans set au début et à la fin de la chaine de
** caractères.
** =======
** #1 : La chaine de caractères préfixe.
** #2 : La chaine de caractères suffixe.
** =======
** Retourne un pointeur sur la nouvelle chaîne,
** ou NULL s'il l'allocation dynamique de mémoire échoue.
*/

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*trimedstr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen((char *)s1 + start);
	if (len != 0)
		while (s1[start + len - 1]
				&& ft_strchr(set, s1[start + len - 1]) != NULL)
			len--;
	if ((trimedstr = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	trimedstr = ft_strncpy(trimedstr, (char *)s1 + start, len);
	trimedstr[len] = '\0';
	return (trimedstr);
}
