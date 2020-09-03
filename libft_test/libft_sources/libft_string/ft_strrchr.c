/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:26:44 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 13:03:30 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Recherche le caractère c dans la chaîne s.
** =========
** #1 : la chaîne de caractère à parser.
** #2 : le caractère à chercher.
** =========
** Retourne un pointeur sur la dernière occurence
** du caractère correspondant, NULL si il n'a pas été trouvé.
*/

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	c2;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	c2 = (char)c;
	while (i > 0)
	{
		if (s[i] == c2)
		{
			return ((char *)(str + i));
		}
		i--;
	}
	if (s[i] == c2)
	{
		return ((char *)(str + i));
	}
	return (NULL);
}
