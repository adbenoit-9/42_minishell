/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:56:29 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:08:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime sur output la chaîne de caractères
** passée en premier argument en suivant les indications
** de formatage si elles existent.
** =========
** #1 : la chaîne de caractère constante,
**		qui contient (ou non) une (des) indication(s) de formatage.
** #(...) : le(s) élément(s) dans l'ordre à formater.
** =========
** Retourne le nombre de caractères imrimés,
** sans compter l'octer nul final.
*/

int		ft_printf(const char *str, ...)
{
	t_position	position;
	int			ret_printed;
	size_t		len;
	va_list		ap;

	position.index = 0;
	position.pos = 0;
	ret_printed = 0;
	va_start(ap, str);
	ft_arg(str, &position, ap, &ret_printed);
	va_end(ap);
	len = position.index - position.pos;
	write(1, (str + position.pos), len);
	ret_printed += len;
	return (ret_printed);
}
