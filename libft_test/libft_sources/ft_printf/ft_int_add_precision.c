/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_add_precision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:53:53 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:31:40 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Alloue (avec malloc(3)) et retourne une chaine de
** caractères représentant un nombre après son formatage de précision.
** =======
** #1 : la chaîne de caractère représentant le nombre à formater. 
** #2 : le champ précision du format.
** =======
** Retourne la chaine de caractères nbr
** une fois le formatage de précision effectué.
*/

char			*ft_int_add_precision(char *nbr, int precision)
{
	int			i;
	int			j;
	int			k;
	int			len;
	char		*precised_int;

	i = 0;
	j = 0;
	len = (int)ft_strlen(nbr);
	if (!(precised_int = (char *)malloc(sizeof(char) * (precision + 2))))
		return (NULL);
	if (nbr[i] == '-')
	{
		precised_int[j++] = nbr[i++];
		len -= 1;
	}
	k = 0;
	while (k++ < (precision - len))
		precised_int[j++] = '0';
	while (nbr[i] != '\0')
		precised_int[j++] = nbr[i++];
	precised_int[j] = '\0';
	return (precised_int);
}
