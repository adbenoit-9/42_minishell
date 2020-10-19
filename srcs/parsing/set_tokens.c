/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 18:27:46 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_tokens(char **word, char **tokens, int k)
{
	(*word)[k] = 0;
	free(*tokens);
	*tokens = NULL;
	if (!(*tokens = ft_strdup(*word)))
		return (MALL_ERR);
	free(*word);
	*word = NULL;
	return (0);
}

int fill_file_name(char ***file, char *str)
{
	size_t	i;
	int 	j;
	int 	size;
	int		len;

	i = 1;
	size = 0;
	while (str[i] == ' ')
			++i;
	if (!(*file))
		size = 0;
	else
	{
		while ((*file)[size])
			++size;
	}
	if (!(*file = realloc_tab(*file, size + 1)))
	{
		ft_free(file, size);
		return (MALL_ERR);
	}
	if ((len = ft_strlen(str + i)) == 0)
		return (SEP_ERR);
	if (!((*file)[size] = malloc(len + 1)))
		return(MALL_ERR);
	j = -1;
	--i;
	while (str[++i])
		(*file)[size][++j] = str[i];
	(*file)[size][j + 1] = 0;
	return (i);
}

int			set_file_name(t_stock **cmd_lst, char *str)
{
	int i;

	i = 0;
	if (str[i] == '<' && str[++i])
		i = fill_file_name(&(*cmd_lst)->input, str);
	else if (str[i])
		i = fill_file_name(&(*cmd_lst)->output, str);
	return (i);
}

int			set_token(char **tokens, t_stock **cmd_lst, char **envp)
{
	int		i;
	int		j;
	int		k;
	int		ret;
	char	*word;

	i = 0;
	word = NULL;
	if (!tokens)
		return (0);
	while (tokens[i])
	{
		k = 0;
		if (!(word = malloc(ft_strlen(tokens[i]) + 1)))
			return (MALL_ERR);
		j = 0;
		while (tokens[i][j])
		{
			ret = 0;
			if (tokens[i][j] == '\\' && tokens[i][++j])
				word[k++] = tokens[i][j++];
			else if (tokens[i][j] == '\'')
				ret = deal_simple_quote(tokens[i] + j, &word, &k, 0);
			else if (tokens[i][j] == '\"')
				ret = deal_double_quote(tokens[i] + j, &word, &k, envp);
			else if (tokens[i][j] == '$')
				ret = deal_dollar(tokens[i] + j, &word, &k,  envp);
			else if (tokens[i][j] == '>' || tokens[i][j] == '<')
			{
				ret = set_file_name(cmd_lst, tokens[i] + j);
				break ;
			}
			else
				word[k++] = tokens[i][j++];
			if (ret == QUOTE_NOT_FOUND || ret == SEP_ERR)
				return (ret);
			else if (ret == VAR_NOT_FOUND)
			{
				(*cmd_lst)->err = VAR_NOT_FOUND;
				word[k] = 0;
				break ;
			}
			else
				j += ret;
		}
		replace_tokens(&word, &tokens[i], k);
		++i;
	}
	return (0);
}
