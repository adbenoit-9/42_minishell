/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:43:04 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/04 14:11:24 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Converti le début de la chaîne pointée en entier.
** =======
** #1: un pointeur vers une chaîne de caractères.
** =======
** Retourne le résultat de la conversion en entier de type int.
*/

int	ft_atoi(const char *str)
{
	int i;
	int minus;
	int nbr;

	i = 0;
	minus = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - 48;
		i++;
	}
	return (nbr * minus);
}
