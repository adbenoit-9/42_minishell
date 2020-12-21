/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:56:50 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 13:53:12 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Vérifie la validité des indications de formatage.
** =========
** #1 : un format.
** =========
** Retourne -1 si le format n'est pas valide,
** 0 si elle l'est.
*/

int	ft_check_format(t_format format)
{
	if (format.flag == -1)
		return (-1);
	else if (format.width == -1)
		return (-1);
	else if (format.precision == -2)
		return (-1);
	else if (format.specifier == '0')
		return (-1);
	else
		return (0);
}
