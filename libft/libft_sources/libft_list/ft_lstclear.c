/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:05:40 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:51:50 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Libère la mémoire de l’élément passé en argument
** en utilisant la fonction del puis avec free(3).
** La mémoire de next ne doit pas être libérée.
** =======
** #1 : l’adresse du pointeur vers un élément.
** #2 : l’adresse de la fonction permettant
**		de supprimer le contenu d’un élément.
** =======
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst != NULL && del != NULL)
	{
		ft_lstclear(&(*lst)->next, del);
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}
