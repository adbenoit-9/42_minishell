/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:21:46 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:39:10 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Calcule la longueur d'un entier n, 
** de type int.
** =========
** #1 : un entier n.
** =========
** Retourne le nombre de chiffre dans n.
*/

size_t	ft_intlen(int n)
{
	int	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}