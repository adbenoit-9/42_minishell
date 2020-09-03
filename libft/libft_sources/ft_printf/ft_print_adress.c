/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:43:16 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:31:48 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime l'adresse d'une variable de type "void"
** obtenue par appel de va_arg() après formatage
** et renvoie le nom total de caractères imprimés.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre total de caractères imprimés.
*/

int		ft_print_adr(t_format format, va_list ap)
{
	void			*adr;
	char			*number;
	int				ret;

	number = NULL;
	ret = 0;
	adr = va_arg(ap, void *);
	if (adr == NULL && format.precision == 0)
	{
		number = ft_zeroes_cp(3, 2);
		ret += ft_put_formatted_nbr(format, number);
	}
	else
		ret = ft_print_adr_cp(adr, format);
	return (ret);
}

/*
** Imprime l'adresse d'une variable de type "void"
** après formatage et renvoie le nom total de caractères imprimés.
** =========
** #1 : un pointeur sur l'adresse mémoire d'une variable.
** #2 : un format.
** =========
** Retourne le nombre total de caractères imprimés.
*/

int		ft_print_adr_cp(void *adr, t_format format)
{
	int		ret;
	char	*number;
	char	*prefix;
	char	*bis;

	ret = 0;
	prefix = ft_zeroes_cp(3, 2);
	number = ft_long_hexitoa((unsigned long)adr, format.specifier);
	if (format.precision >= (int)ft_strlen(number))
	{
		ft_putstr(prefix);
		ret += 2;
		ret += ft_put_formatted_nbr(format, number);
	}
	else
	{
		bis = ft_join(prefix, number);
		ret += ft_put_formatted_nbr(format, bis);
		free(number);
	}
	free(prefix);
	return (ret);
}
