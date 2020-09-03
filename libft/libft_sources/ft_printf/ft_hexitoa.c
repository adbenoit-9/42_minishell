/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:28:28 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:31:35 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Alloue (avec malloc(3)) et retourne une chaine de
** caractères représentant un unsigned integer n reçu en argument.
** =======
** #1 : l'integer à convertir.
** #2 : le specifier indiquant si la base est en MAJ ou MIN.
** =======
** Retourne la chaine de caractères représentant l’integer,
** NULL si l’allocation échoue.
*/

char	*ft_hexitoa(unsigned int n, char c)
{
	char	*str;
	char	*base;
	size_t	len;

	str = NULL;
	if (c == 'x' || c == 'p')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	len = ft_hexintlen(n);
	if (len > 1)
		len -= 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		str[len] = '\0';
		while (len > 0)
		{
			str[len - 1] = base[(n % 16)];
			len--;
			n = n / 16;
		}
	}
	return (str);
}

/*
** Alloue (avec malloc(3)) et retourne une chaine de
** caractères représentant un unsigned long n reçu en argument.
** =======
** #1 : l'integer à convertir.
** #2 : le specifier indiquant si la base est en MAJ ou MIN.
** =======
** Retourne la chaine de caractères représentant l’integer,
** NULL si l’allocation échoue.
*/

char	*ft_long_hexitoa(unsigned long n, char c)
{
	char	*str;
	char	*base;
	size_t	len;

	str = NULL;
	if (c == 'x' || c == 'p')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	len = ft_long_hexintlen(n);
	if (len > 1)
		len -= 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str != NULL)
	{
		str[len] = '\0';
		while (len > 0)
		{
			str[len - 1] = base[(n % 16)];
			len--;
			n = n / 16;
		}
	}
	return (str);
}
