/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:26:25 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:12:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Vérifie si le caractère c est un espace.
** =========
** #1 : le carctère à analyser.
** =========
** Retourne 1 si c'est le cas (VRAI),
** 0 si ce n'est pas le cas (FAUX).
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
