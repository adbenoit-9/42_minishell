/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:57:24 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:05:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Ajoute l’élément new à la fin de la liste.
** =======
** #1 : l’adresse du pointeur vers le premier élément de la liste.
** #2 : l’adresse du pointeur vers l’élément à rajouterà la liste.
** =======
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (*alst != NULL)
	{
		while ((*alst)->next != NULL)
			(*alst) = (*alst)->next;
		(*alst)->next = new;
	}
	else
		(*alst) = new;
}
