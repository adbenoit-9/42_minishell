/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/31 00:15:50 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_char(char *token, t_list **new, int *k, char *envp[])
{
	int	ret;

	if (token[0] == '\'')
		ret = deal_simple_quote(token, (*new)->content, k, 0);
	else if (token[0] == '\"')
		ret = deal_double_quote(token, new, k, envp);
	else if (token[0] == '$' && token[1] == '?')
		ret = deal_status(&(*new)->content, k, ft_strlen(token));
	else if (token[0] == '$')
		ret = deal_dollar(token, new, k, envp);
	else if (token[0] == ' ')
		ret = 1;
	else
	{
		(*new)->content[(*k)++] = token[0];
		ret = 1;
	}
	return (ret);
}

int			parse_token(char *token, t_list **new, t_cmd **cmd, char *env[])
{
	int		j;
	int		k;
	int		ret;
	t_list	*tmp;

	k = 0;
	j = 0;
	ret = 0;
	tmp = *new;
	while (ret >= 0 && token[j])
	{
		ret = 0;
		if (tmp->next)
			tmp = ft_lstlast(*new);
		if (token[j] == '\\' && token[++j])
			tmp->content[k++] = token[j++];
		else if (token[0] == '>' || token[0] == '<')
			return (set_file_name(cmd, token + j, env));
		else
			ret = parse_char(token + j, &tmp, &k, env);
		j = (ret > 0) ? j + ret : j;
	}
	tmp = ft_lstlast(tmp);
	tmp->content[k] = 0;
	return (ret);
}

int			set_token(char **tokens, t_cmd **cmd, char *envp[])
{
	int		i;
	int		ret;
	t_list	*new;

	i = -1;
	while (tokens[++i])
	{
		if (!(new = ft_lstnew(ft_strdup(tokens[i]))) || !new->content)
		{
			ft_lstclear(&new, free);
			return (MALL_ERR);
		}
		if ((ret = parse_token(tokens[i], &new, cmd, envp)) < -1)
		{
			ft_lstclear(&new, free);
			return (ret);
		}
		if (ret == -1)
			ft_lstclear(&new, free);
		else
			ft_lstadd_back(&(*cmd)->tok, new);
	}
	return (0);
}
