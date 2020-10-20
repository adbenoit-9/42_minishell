/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/20 16:02:37 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_token(char **word, char **tokens, int k)
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

static int 	parse_file(char **file, char *str, t_stock **cmd_lst, char **envp)
{
	size_t	i;
	int 	j;
	int		len;

	i = 1;
	while (str[i] == ' ')
			++i;
	if (*file)
		free(*file);
	if ((len = ft_strlen(str + i)) == 0)
		return (SEP_ERR);
	if (!(*file = malloc(len + 1)))
		return(MALL_ERR);
	j = -1;
	--i;
	while (str[++i])
		(*file)[++j] = str[i];
	(*file)[j + 1] = 0;
	parse_token(file, cmd_lst, envp);
	return (i);
}

int			set_file_name(t_stock **cmd_lst, char *str, char **envp)
{
	int i;
	int fd;

	i = 0;
	if (str[i] == '<' && str[++i])
	{
		i = parse_file(&(*cmd_lst)->input, str, cmd_lst, envp);
		errno = 0;
		fd = open((*cmd_lst)->input, O_RDONLY);
		if (i > 0 && fd == -1)
		{
			write_error((*cmd_lst)->input, ": ", strerror(errno));
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);

	}
	else if (str[i])
	{
		i = parse_file(&(*cmd_lst)->output, str, cmd_lst, envp);
		errno = 0;
		fd = open((*cmd_lst)->output, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if (fd == -1)
		{
			write_error((*cmd_lst)->output, ": ", strerror(errno));
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);
	}
	return (i);
}

int			parse_token(char **token, t_stock **cmd_lst, char **envp)
{
	int		j;
	int		k;
	int		ret;
	char	*word;

	k = 0;
	if (!(word = malloc(ft_strlen((*token)) + 1)))
		return (MALL_ERR);
	j = 0;
	while ((*token)[j])
	{
		ret = 0;
		if ((*token)[j] == '\\' && (*token)[++j])
			word[k++] = (*token)[j++];
		else if ((*token)[j] == '\'')
			ret = deal_simple_quote((*token) + j, &word, &k, 0);
		else if ((*token)[j] == '\"')
			ret = deal_double_quote((*token) + j, &word, &k, envp);
		else if ((*token)[j] == '$')
			ret = deal_dollar((*token) + j, &word, &k,  envp);
		else if ((*token)[j] == '>' || (*token)[j] == '<')
			ret = set_file_name(cmd_lst, (*token) + j, envp);
		else
			word[k++] = (*token)[j++];
		if (ret < -1)
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
	replace_token(&word, token, k);
	return (0);
}

int			set_token(char **tokens, t_stock **cmd_lst, char **envp)
{
	int	i;
	int	ret;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
	{
		if ((ret = parse_token(&(tokens[i]), cmd_lst, envp)) != 0)
			return (ret);
		++i;
	}
	return (0);
}
