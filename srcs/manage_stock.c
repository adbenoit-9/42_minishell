/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:18:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/16 14:29:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stock			*ft_stocknew(int cmd)
{
	t_stock	*list;

	if (!(list = (t_stock *)malloc(sizeof(t_stock))))
		return (NULL);
	list->cmd = cmd;
	list->ret = 0;
	list->err = 0;
	list->sep = NONE;
	list->input = NULL;
	list->stdin = NULL;
	list->stdout = NULL;
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

void			ft_stockclear(t_stock **lst, void (del)(t_stock**))
{
	if (*lst != NULL && del != NULL)
	{
		ft_stockclear(&(*lst)->next, del);
		del(lst);
		*lst = NULL;
	}
}
