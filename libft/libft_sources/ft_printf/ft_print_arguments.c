/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:37:11 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 14:19:37 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Dirige le formatage de la partie de str
** selon le specifier et l'imprime.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre total de caractères imprimés.
*/

int	ft_print_arguments(t_format format, va_list ap)
{
	int ret_arg_printed;

	ret_arg_printed = 0;
	if (format.specifier == 'c')
		ret_arg_printed += ft_print_c(format, ap);
	else if (format.specifier == 's')
		ret_arg_printed += ft_print_str(format, ap);
	else if (format.specifier == 'p')
		ret_arg_printed += ft_print_adr(format, ap);
	else if (format.specifier == 'd' || format.specifier == 'i')
		ret_arg_printed += ft_print_signed_dec(format, ap);
	else if (format.specifier == 'u')
		ret_arg_printed += ft_print_unsigned_dec(format, ap);
	else if (format.specifier == 'x' || format.specifier == 'X')
		ret_arg_printed += ft_print_hex(format, ap);
	else if (format.specifier == '%')
		ret_arg_printed += ft_print_per(format);
	return (ret_arg_printed);
}
