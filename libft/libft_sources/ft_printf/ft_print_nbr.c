/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:30 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:09:33 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime le caractère un nombre de type "signed int"
** obtenu par appel de va_arg() après formatage
** et renvoie le nom total de caractères imprimés.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre total de caractères imprimés,
** -1 en cas d'erreur.
*/

int		ft_print_signed_dec(t_format format, va_list ap)
{
	signed int	nbr;
	char		*number;

	nbr = (signed int)va_arg(ap, int);
	if (nbr == 0 && format.width == 0 && format.precision >= 0)
		number = ft_zeroes_cp(0, 1);
	else if (nbr == 0 && format.width >= 1 && format.precision == 0)
	{
		number = ft_zeroes_cp(1, 1);
		format.flag = 0;
	}
	else if (format.width >= 1 && format.precision >= 0 && format.flag == 1)
	{
		if (nbr == 0)
			number = ft_zeroes_cp(2, 1);
		else
			number = ft_itoa(nbr);
		format.flag = 0;
	}
	else
		number = ft_itoa(nbr);
	return (ft_put_formatted_nbr(format, number));
}

/*
** Imprime un nombre de type "unsigned int"
** obtenu par appel de va_arg() après formatage
** et renvoie le nom total de caractères imprimés.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre total de caractères imprimés,
** -1 en cas d'erreur.
*/

int		ft_print_unsigned_dec(t_format format, va_list ap)
{
	unsigned int	nbr;
	char			*number;

	nbr = (unsigned int)va_arg(ap, int);
	if (nbr == 0 && format.width == 0 && format.precision >= 0)
		number = ft_zeroes_cp(0, 1);
	else if (nbr == 0 && format.width >= 1 && format.precision == 0)
	{
		number = ft_zeroes_cp(1, 1);
		format.flag = 0;
	}
	else if (format.width >= 1 && format.precision >= 0 && format.flag == 1)
	{
		if (nbr == 0)
			number = ft_zeroes_cp(2, 1);
		else
			number = ft_uitoa(nbr);
		format.flag = 0;
	}
	else
		number = ft_uitoa(nbr);
	return (ft_put_formatted_nbr(format, number));
}

/*
** Imprime un nombre de type "unsigned long"
** obtenu par appel de va_arg() après formatage
** et renvoie le nom total de caractères imprimés.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre total de caractères imprimés,
** -1 en cas d'erreur.
*/

int		ft_print_hex(t_format format, va_list ap)
{
	unsigned long	nbr;
	char			*number;

	nbr = (unsigned long)va_arg(ap, int);
	if (nbr == 0 && format.width == 0 && format.precision >= 0)
		number = ft_zeroes_cp(0, 1);
	else if (nbr == 0 && format.width >= 1 && format.precision == 0)
	{
		number = ft_zeroes_cp(1, 1);
		format.flag = 0;
	}
	else if (format.width >= 1 && format.precision >= 0 && format.flag == 1)
	{
		if (nbr == 0)
			number = ft_zeroes_cp(2, 1);
		else
			number = ft_hexitoa(nbr, format.specifier);
		format.flag = 0;
	}
	else
		number = ft_hexitoa(nbr, format.specifier);
	return (ft_put_formatted_nbr(format, number));
}

/*
** Alloue (avec malloc(3)) et gère les cas particuliers
** en cas de valeur nulle des nombres à formater et
** selon le format donné.
** =========
** #1 : le particulier à traiter.
** #2 : la (taille -1) à allouer pour la chaîne correspondante.
** =========
** Retourne la chaîne de caractères représentant
** le nombre à formatter, NULL si l'allocation échoue.
*/

char	*ft_zeroes_cp(int cp, int size)
{
	char	*number;

	if (!(number = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (cp >= 0 && cp <= 2)
	{
		if (cp == 0)
			number[0] = 0;
		else if (cp == 1)
			number[0] = ' ';
		else if (cp == 2)
			number[0] = '0';
		number[1] = '\0';
	}
	else if (cp == 3)
	{
		number[0] = '0';
		number[1] = 'x';
		number[2] = '\0';
	}
	return (number);
}
