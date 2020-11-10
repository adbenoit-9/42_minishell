/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:46:12 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:12:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Cherche la première occurrence de la sous-chaîne needle
** au sein de la chaîne haystack dans laquelle pas plus de
** len caractères sont examinés.
** Les caractères nuls de fin ne sont pas comparés.
** =========
** #1 : une chaîne de caractères à examiner.
** #2 : une chaîne de caractères à chercher.
** #3 : le nombre maximal de caractères à parser.
** =========
** Retourne un pointeur sur le premier caractère de la première
** occurence de needle dans haystack, haystack si needle est une chaîne vide,
** ou NULL si needle n'est pas trouvée dans haystack.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t pos;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	pos = 0;
	while (haystack[pos] != '\0' && (size_t)pos < len)
	{
		if (haystack[pos] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' &&
			haystack[pos + i] == needle[i] && (size_t)(pos + i) < len)
				++i;
			if (needle[i] == '\0')
				return ((char *)haystack + pos);
		}
		++pos;
	}
	return (NULL);
}
