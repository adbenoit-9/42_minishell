/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 01:08:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/02 15:25:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_cmdnew(int sep)
{
	t_cmd	*list;

	if (!(list = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	list->r_type = 0;
	list->err = 0;
	list->sep = sep;
	list->tok = NULL;
	list->input = NULL;
	list->output = NULL;
	list->next = NULL;
	list->pwd = NULL;
	return (list);
}

static t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void			ft_cmdadd_back(t_cmd **alst, t_cmd *new)
{
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
			ft_cmdlast(*alst)->next = new;
	}
}

void			clear_one(t_cmd **lst)
{
	ft_lstclear(&(*lst)->tok, free);
	ft_lstclear(&(*lst)->input, free);
	ft_lstclear(&(*lst)->output, free);
	free((*lst)->pwd);
	(*lst)->pwd = NULL;
	free(*lst);
}

void			ft_cmdclear(t_cmd **lst, void (del)(t_cmd**))
{
	if (*lst != NULL && del != NULL)
	{
		ft_cmdclear(&(*lst)->next, del);
		del(lst);
		*lst = NULL;
	}
}
