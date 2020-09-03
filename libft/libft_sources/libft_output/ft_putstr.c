/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:15:25 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 14:42:10 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Écrit la chaîne de caractères s.
** =========
** #1 : la chaîne à écrire.
** =========
*/

void	ft_putstr(char *s)
{
	if (s != NULL)
		write(1, s, ft_strlen(s));
}
