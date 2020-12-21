/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:25:15 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/17 15:00:32 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libftprintf.h"

/*
** Alloue et initialise une chaîne avec un caractère donné.
** =========
** #1 : la taille de la chaîne à créer.
** #2 : le caractère servant à initialiser la chaîne.
** =========
** Retourne la chaîne résultante, NULL si l'allocation échoue.
*/

char	*ft_calloc_flag(size_t count, int c)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = (char*)malloc(sizeof(char) * (count + 1));
	if (mem != NULL)
	{
		while (i < count)
		{
			mem[i] = c;
			i++;
		}
		mem[i] = '\0';
	}
	return (mem);
}
