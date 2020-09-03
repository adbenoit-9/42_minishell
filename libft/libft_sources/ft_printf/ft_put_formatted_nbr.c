/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_formatted_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:00:24 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 21:21:48 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime une chaîne de caractère (post-itoa), après formatage.
** =========
** #1 : un format.
** #2 : une chaîne de caractère.
** =========
** Retourne le nombre total de caractères imprimés,
** -1 en cas d'erreur.
*/

int		ft_put_formatted_nbr(t_format format, char *number)
{
	int		len;
	int		p;
	char	*precised;
	char	*with_width;

	len = -1;
	len = ft_strlen(number);
	if (number[0] == '-')
		len -= 1;
	if (format.precision <= len)
		p = len;
	else
		p = format.precision;
	precised = ft_int_add_precision(number, p);
	free(number);
	len = ft_strlen(precised);
	if (format.width <= len)
		format.width = len;
	with_width = ft_int_add_width(format, precised);
	free(precised);
	len = ft_strlen(with_width);
	ft_putstr(with_width);
	free(with_width);
	return (len);
}
