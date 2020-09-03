/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 09:52:07 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 14:21:16 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Alloue (avec malloc(3)) et retourne une nouvelle
** chaine, résultat de la concaténation de s1 et s2.
** =======
** #1 : La chaine de caractères préfixe.
** #2 : La chaine de caractères suffixe.
** =======
** Retourne un pointeur sur la nouvelle chaîne,
** s1 si s2 est NULL, s2 si s1 est NULL,
** ou NULL si l'allocation dynamique de mémoire échoue.
*/

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (ft_str_null(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
** Gère les cas particuliers de ft_join(2).
** =======
** #1 : La chaine de caractères préfixe.
** #2 : La chaine de caractères suffixe.
** =======
** Retourne un pointeur sur s1 si s2 est NULL,
** s2 si s1 est NULL, ou NULL sinon.
*/

char	*ft_str_null(char *s1, char *s2)
{
	if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	else
		return (NULL);
}
