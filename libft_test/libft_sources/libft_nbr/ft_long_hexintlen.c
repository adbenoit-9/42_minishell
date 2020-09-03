/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_hexintlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:23:24 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:45:25 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Calcule la longueur d'un entier n,
** de type unsigned long int, en base octale.
** =========
** #1 : un entier n.
** =========
** Retourne la longueur de n.
*/

size_t	ft_long_hexintlen(unsigned long int n)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
