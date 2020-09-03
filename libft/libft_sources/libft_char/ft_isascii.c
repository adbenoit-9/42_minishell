/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:03 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/18 17:47:57 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Vérifie si le caractère c est un unsigned char sur 7 bits,
** entrant dans le jeu de caractère de la table ASCII.
** =========
** #1 : le carctère à analyser.
** =========
** Retourne 1 si c'est le cas (VRAI),
** 0 si ce n'est pas le cas (FAUX).
*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
