/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:08:53 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/21 17:36:07 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime les parties de la chaîne de caractères principale de ft_printf()
** qui ne nécessitent pas de conversion.
** =========
** #1 : la chaîne de caractères, premier argument de ft_printf(). 
** #2 : un pointeur sur la position actuelle dans str.
** =========
** Retourne le nombre de caractère imprimés.
*/

int		ft_get_string(const char *str, size_t *ptr_pos)
{
	size_t	j;
	size_t	k;
	char	*line;

	j = *ptr_pos;
	k = 0;
	while (str[*ptr_pos] != '%')
	{
		*ptr_pos += 1;
		k++;
	}
	*ptr_pos += 1;
	if (!(line = malloc(sizeof(char) * (k + 1))))
		return (-1);
	k = 0;
	while (str[j] != '%')
		line[k++] = str[j++];
	ptr_pos += 1;
	write(1, line, k);
	free(line);
	return (k);
}
