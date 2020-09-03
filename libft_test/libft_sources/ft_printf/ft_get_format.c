/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:16:47 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 15:21:22 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Récupère l'indication de formatage flag.
** =========
** #1 : la chaîne de caractères à formater.
** #2 : un pointeur sur la position actuelle
** 		dans la chaîne de caractères (= adresse de l'index).
** =========
** Retourne le format, contenant désormais le flag :
** 0 si aucun flag, 1 si le flag est '0', 2 si le flag est '-'
** (le flag '0' est ignoré quand le flag '-' est présent).  
*/

t_format	ft_f(const char *str, size_t *ptr_pos, t_format form)
{
	form.flag = 0;
	if (str[*ptr_pos] == '0')
	{
		while (str[*ptr_pos] == '0')
			*ptr_pos += 1;
		if (str[*ptr_pos] == '-')
		{
			*ptr_pos += 1;
			form.flag = 2;
		}
		else
			form.flag = 1;
	}
	else if (str[*ptr_pos] == '-')
	{
		while (str[*ptr_pos] == '-')
			*ptr_pos += 1;
		if (str[*ptr_pos] == '0')
			*ptr_pos += 1;
		form.flag = 2;
	}
	return (form);
}

/*
** Récupère l'indication de formatage width,
** modifie le flag dans le cas où width < 0 
** (le '-' est alors considéré comme un flag).
** =========
** #1 : la chaîne de caractères à formater.
** #2 : un pointeur sur la position actuelle
** 		dans la chaîne de caractère (= adresse de l'index).
** #3 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le format, contenant désormais la width.
*/

t_format	ft_w(const char *s, size_t *p_pos, va_list ap, t_format form)
{
	int	width;

	width = 0;
	if (s[*p_pos] == '*')
	{
		width = va_arg(ap, int);
		if (width < 0)
		{
			form.flag = 2;
			form.width = (-width);
		}
		else
			form.width = width;
		*p_pos += 1;
	}
	else if (ft_isdigit(s[*p_pos]) == 1)
	{
		while (ft_isdigit(s[*p_pos]) == 1)
		{
			width = (width * 10) + s[*p_pos] - 48;
			*p_pos += 1;
		}
		form.width = width;
	}
	return (form);
}

/*
** Récupère l'indication de formatage precision.
** =========
** #1 : la chaîne de caractères à formater.
** #2 : un pointeur sur la position actuelle
** 		dans la chaîne de caractères (= adresse de l'index).
** #3 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne le format, contenant désormais la précision :
** un entier positif ou -1 en cas d'erreur.
*/

t_format	ft_p(const char *s, size_t *p_pos, va_list ap, t_format form)
{
	form.precision = -1;
	if (s[*p_pos] == '.')
	{
		form.precision = 0;
		*p_pos += 1;
		if (s[*p_pos] == '*')
		{
			form.precision = va_arg(ap, int);
			if (form.precision < 0)
				form.precision = -1;
			*p_pos += 1;
		}
		else if (ft_isdigit(s[*p_pos]) == 1)
		{
			while (ft_isdigit(s[*p_pos]) == 1)
			{
				form.precision = (form.precision * 10) + s[*p_pos] - 48;
				*p_pos += 1;
			}
		}
		else
			form.dot = 1;
	}
	return (form);
}

/*
** Récupère l'indication de formatage specifier.
** =========
** #1 : la chaîne de caractères à formater.
** #2 : un pointeur sur la position actuelle
** 		dans la chaîne de caractères (= adresse de l'index).
** =========
** Retourne la valeur correspondante avec
** '0' s'il n'y a pas de precision.
*/

char		ft_s(const char *str, size_t *ptr_pos)
{
	char specifier;

	specifier = '0';
	if (str[*ptr_pos] == 's')
		specifier = 's';
	else if (str[*ptr_pos] == 'c')
		specifier = 'c';
	else if (str[*ptr_pos] == '%')
		specifier = '%';
	else if (str[*ptr_pos] == 'p')
		specifier = 'p';
	else if (str[*ptr_pos] == 'd')
		specifier = 'd';
	else if (str[*ptr_pos] == 'i')
		specifier = 'i';
	else if (str[*ptr_pos] == 'u')
		specifier = 'u';
	else if (str[*ptr_pos] == 'x')
		specifier = 'x';
	else if (str[*ptr_pos] == 'X')
		specifier = 'X';
	*ptr_pos += 1;
	return (specifier);
}

/*
** Collecte les indications de formatage flag, width,
** precision et specifier et affecte les différentes
** valeurs à une variable de type form.
** =========
** #1 : la chaîne de caractères à formater.
** #2 : un pointeur sur la position actuelle
** 		dans la chaîne de caractères (= adresse de l'index).
** #3 : un pointeur sur l'élément actuel de la liste d'arguments.
** =========
** Retourne la valeur correspondante.
*/

t_format	ft_get_format(const char *str, size_t *ptr_pos, va_list ap)
{
	t_format	form;

	form.flag = 0;
	form.width = 0;
	form.precision = 0;
	form.dot = 0;
	form.specifier = '0';
	form = ft_f(str, ptr_pos, form);
	form = ft_w(str, ptr_pos, ap, form);
	form = ft_p(str, ptr_pos, ap, form);
	form.specifier = ft_s(str, ptr_pos);
	return (form);
}
