/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:23:26 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/10 01:05:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Itère sur la liste lst et applique la fonction f au
** contenu de chaque élément. Crée une nouvelle liste
** résultant des applications successives de f. la
** fonction del est la pour detruire le contenu d'un
** element si necessaire.
** Retourne la nouvelle liste ou NULL si l’allocation échoue.
** =======
** #1 : l’adresse du pointeur vers un élément.
** #2 : l’adresse de la fonction à appliquer.
** =======
** Retourne la nouvelle liste, NULL si l’allocation échoue.
*/

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*first;
	t_list		*map;

	if (lst == NULL)
		return (NULL);
	if (!(map = ft_lstnew(f(lst))))
		return (NULL);
	first = map;
	while (lst != NULL)
	{
		if (lst->next != NULL)
		{
			if (!(map->next = ft_lstnew((*f)(lst->next))))
			{
				ft_lstclear(&first, del);
				return (0);
			}
			map = map->next;
		}
		lst = lst->next;
	}
	map = 0;
	return (first);
}
