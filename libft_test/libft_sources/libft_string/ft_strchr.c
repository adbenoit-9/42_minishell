/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:21:37 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:51:38 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Recherche le caractère c dans la chaîne s.
** =========
** #1 : la chaîne de caractère à parser.
** #2 : le caractère à chercher.
** =========
** Retourne un pointeur sur le caractère correspondant, 
** NULL si il n'a pas été trouvé.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (char *)(s + i);
		}
		i++;
	}
	if (s[i] == c)
		return ((char*)s + i);
	return (NULL);
}
