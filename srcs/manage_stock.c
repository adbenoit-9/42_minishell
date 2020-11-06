/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:18:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 00:25:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stock			*ft_stocknew(int sep)
{
	t_stock	*list;

	if (!(list = (t_stock *)malloc(sizeof(t_stock))))
		return (NULL);
	list->r_type = 0;
	list->err = 0;
	list->sep = sep;
	list->tokens = NULL;
	list->input = NULL;
	list->output = NULL;
	list->next = NULL;
	return (list);
}

static t_stock	*ft_stocklast(t_stock *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void			ft_stockadd_back(t_stock **alst, t_stock *new)
{
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
			ft_stocklast(*alst)->next = new;
	}
}

void	clear_one(t_stock **lst)
{
	ft_free((*lst)->tokens);
	free((*lst)->input);
	free((*lst)->output);
	(*lst)->tokens = NULL;
	(*lst)->input = NULL;
	(*lst)->output = NULL;
	free(*lst);
}

void			ft_stockclear(t_stock **lst, void (del)(t_stock**))
{
	if (*lst != NULL && del != NULL)
	{
		ft_stockclear(&(*lst)->next, del);
		del(lst);
		*lst = NULL;
	}
}
