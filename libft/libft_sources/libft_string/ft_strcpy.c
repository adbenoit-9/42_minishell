/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:17:53 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:51:42 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Copie la chaîne pointée par src (y compris l'octet nul final)
** dans la chaîne pointée par dst.
** Les deux chaînes ne doivent pas se chevaucher.
** La chaîne dest doit être assez grande pour accueillir la copie.
** =========
** #1 : la chaîne de destination.
** #2 : la chaîne source.
** =========
** Retourne la longueur de n.
*/

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
