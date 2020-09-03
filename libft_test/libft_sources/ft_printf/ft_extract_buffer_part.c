/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_buffer_part.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:23:53 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 14:10:20 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Alloue et crée une chaîne de caractères
** dans laquelle sont copiés n caractères de la chaîne source.
** =========
** #1 : le nombre de caractères à extraire.
** #2 : la chaîne dans laquelle extraire le(s) caractère(s).
** =========
** Retourne la nouvelle chaîne de caractères créée,
** NULL en cas d'erreur.
*/

char	*ft_extract_buffer_part(int precision, char *buffer)
{
	int		i;
	char	*ret;

	i = 0;
	if (precision == -1)
		precision = (int)ft_strlen(buffer);
	ret = (char*)malloc(sizeof(char) * (precision + 1));
	while (i < precision)
	{
		ret[i] = buffer[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
