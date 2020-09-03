/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_add_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:51:00 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/22 12:24:56 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Crée une nouvelle chaîne de caractères en concaténant
** un caractère donné et chaîne source.
** =========
** #1 : un caractère donné
** #2 : la chaîne de caractères à ajouter après.
** =========
** Retourne la nouvelle chaîne de caractères créée,
** NULL en cas d'erreur.
*/

char	*ft_add_front_to_char(char c, char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!(new_str = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	new_str[i] = c;
	i++;
	while (str[j] != '\0')
	{
		new_str[i] = str[j];
		j++;
		i++;
	}
	free(str);
	new_str[i] = '\0';
	return (new_str);
}

/*
** Crée une nouvelle chaîne de caractères en concaténant
** une chaîne source et un caractère donné.
** =========
** #1 : un caractère donné
** #2 : la chaîne de caractères à ajouter avant.
** =========
** Retourne la nouvelle chaîne de caractères créée,
** NULL en cas d'erreur.
*/

char	*ft_add_back_to_char(char c, char *str)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	if (!(new_str = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	new_str[i] = c;
	i++;
	new_str[i] = '\0';
	return (new_str);
}
