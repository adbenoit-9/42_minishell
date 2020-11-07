/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/07 14:20:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_token(char *token, char **new, t_stock **cmd, char **envp)
{
	int		j;
	int		k;
	int		ret;

	k = 0;
	if (!(*new = malloc(ft_strlen(token) + 1)))
		return (MALL_ERR);
	j = 0;
	while (token[j])
	{
		ret = 0;
		if (token[j] == '\\' && token[++j])
			(*new)[k++] = token[j++];
		else if (token[j] == '\'')
			ret = deal_simple_quote(token + j, new, &k, 0);
		else if (token[j] == '\"')
			ret = deal_double_quote(token + j, new, &k, envp);
		else if (token[j] == '$' && token[j + 1] == '?')
			ret = deal_status(new, &k, ft_strlen(token));
		else if (token[j] == '$')
			ret = deal_dollar(token + j, new, &k, envp);
		else if (token[j] == '>' || token[j] == '<')
			return (set_file_name(cmd, token + j, envp));
		else if (token[j] == ' ')
			ret = 1;
		else
			(*new)[k++] = token[j++];
		if (ret < 0)
			break ;
		j += ret;
	}
	(*new)[k] = 0;
	return (ret);
}

int			set_token(char **tokens, t_stock **cmd, char **envp)
{
	int	i;
	int	ret;
	int	k;

	k = 0;
	if (!((*cmd)->tokens = malloc((sizeof(char *) * (ft_tabsize(tokens) + 1)))))
	{
		ft_free(tokens);
		return (MALL_ERR);
	}
	i = -1;
	while (tokens[++i])
	{
		if ((ret = parse_token(tokens[i], &(*cmd)->tokens[k],
		cmd, envp)) < -1)
		{
			ft_free(tokens);
			(*cmd)->tokens[++k] = NULL;
			return (ret);
		}
		if (ret != -1)
			++k;
	}
	ft_free(tokens);
	(*cmd)->tokens[k] = NULL;
	return (0);
}
