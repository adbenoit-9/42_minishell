/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:09:19 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:10:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Alloue (avec malloc(3)) et retourne une chaine de caractères
** issue de la chaine ’s’. Cette nouvelle chaine commence à l’index
** start et a pour taille maximale len.
** =======
** #1 : la chîne de laquelle extraire la nouvelle chaîne.
** #2 : l'index de début de la nouvelle chaîne s.
** #3 : la taille maximale de la nouvelle chapine.
** =======
** Retourne un pointeur sur la nouvelle chaîne,
** ou NULL s'il l'allocation dynamique de mémoire échoue.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = (char *)malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
