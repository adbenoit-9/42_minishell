/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:17:15 by mabriand          #+#    #+#             */
/*   Updated: 2020/12/23 20:51:11 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Alloue (avec malloc(3)) et renvoie un nouvel
** élément. la variable content est initialisée à
** l’aide de la valeur du paramètre content.
** La variable next est initialisée à NULL.
** =======
** #1 : un pointeur sur la donnée contenue dans le maillon.
** =======
** Retourne un nouvel élément de type t_list.
*/

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	else
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}
