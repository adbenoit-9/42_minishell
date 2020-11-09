/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/09 17:08:50 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_char(char *token, char **new, int *k, char **envp)
{
	int	ret;

	if (token[0] == '\'')
		ret = deal_simple_quote(token, new, k, 0);
	else if (token[0] == '\"')
		ret = deal_double_quote(token, new, k, envp);
	else if (token[0] == '$' && token[1] == '?')
		ret = deal_status(new, k, ft_strlen(token));
	else if (token[0] == '$')
		ret = deal_dollar(token, new, k, envp);
	else if (token[0] == ' ')
		ret = 1;
	else
	{
		(*new)[(*k)++] = token[0];
		ret = 1;
	}
	return (ret);
}

int			parse_token(char *token, char **new, t_stock **cmd, char **envp)
{
	int		j;
	int		k;
	int		ret;

	k = 0;
	if (!(*new = malloc(ft_strlen(token) + 1)))
		return (MALL_ERR);
	j = 0;
	ret = 0;
	while (ret >= 0 && token[j])
	{
		ret = 0;
		if (token[j] == '\\' && token[++j])
			(*new)[k++] = token[j++];
		else if (token[0] == '>' || token[0] == '<')
		{
			(*new)[k] = 0;
			return (set_file_name(cmd, token, envp));
		}
		else
			ret = parse_char(token + j, new, &k, envp);
		j = (ret > 0) ? j + ret : j;
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
		k = (ret != -1) ? k + 1 : k;
	}
	ft_free(tokens);
	(*cmd)->tokens[k] = NULL;
	return (0);
}
