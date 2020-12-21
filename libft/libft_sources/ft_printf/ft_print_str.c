/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:13:14 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:08:08 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Imprime une chaîne de caractères
** selon les instructions de formatage.
** =========
** #1 : un format.
** #2 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le nombre de caractères imprimés.
*/

int		ft_print_str(t_format format, va_list ap)
{
	char	*str;
	int		nbr_space;
	char	*printed;
	char	*new_buffer;
	char	*to_add;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	nbr_space = ft_format_trans(&format.precision, &format.width, str);
	new_buffer = ft_extract_buffer_part(format.precision, str);
	to_add = ft_to_add(format.flag, nbr_space);
	printed = ft_printed(format.flag, new_buffer, to_add);
	free(to_add);
	free(new_buffer);
	ft_putstr(printed);
	free(printed);
	return (nbr_space + format.precision);
}

/*
** Calcule le nombre de caractères ('0' ou ' ') à ajouter
** pour une chaîne, en fonction des indications de formatage.
** =========
** #1 : un pointeur sur le champ précision du format.
** #2 : un pointeur sur le champ largeur du format.
** #3 : la chapine de caractère à formater.
** =========
** Retourne le nombre de caractères à ajouter lors du formatage.
*/

int		ft_format_trans(int *ptr_precision, int *ptr_width, char *str)
{
	int nbr_space;
	int len;

	nbr_space = 0;
	len = ft_strlen(str);
	if (*ptr_precision > len || *ptr_precision < 0)
		*ptr_precision = len;
	if ((*ptr_width >= *ptr_precision) && (*ptr_precision < len))
		nbr_space = *ptr_width - *ptr_precision;
	else if (*ptr_width > len)
		nbr_space = *ptr_width - len;
	return (nbr_space);
}

/*
** Crée la chaîne de caractères
** à ajouter à celle qu'il faut formater.
** =========
** #1 : le champ flag du format.
** #2 : le nombre de caractères de la chaîne à créer.
** =========
** Retourne la chaîne à ajouter lors du formatage.
*/

char	*ft_to_add(int flag, int nbr_space)
{
	char *to_add;

	if (flag == 1)
		to_add = ft_calloc_flag(nbr_space, 48);
	else
		to_add = ft_calloc_flag(nbr_space, 32);
	return (to_add);
}

/*
** Crée la chaîne finale formattée
** en fonction du champ flag du format.
** =========
** #1 : le champ flag du format.
** #2 : la chaîne de caractères extraite de l'originale.
** #3 : la chaîne à ajouter.
** =========
** Retourne la chaîne à imprimer, après formatage.
*/

char	*ft_printed(int flag, char *new_buffer, char *to_add)
{
	char *printed;

	if (flag == 2)
		printed = ft_join(new_buffer, to_add);
	else
		printed = ft_join(to_add, new_buffer);
	return (printed);
}
