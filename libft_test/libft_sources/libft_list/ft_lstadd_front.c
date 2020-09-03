/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:38:55 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:51:48 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Ajoute l’élément new au début de la liste.
** =======
** #1 : l’adresse du pointeur vers le premier élément de la liste.
** #2 : l’adresse du pointeur vers l’élément à rajouterà la liste.
** =======
*/

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (*alst != NULL && new != NULL)
		new->next = *alst;
	*alst = new;
}