/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:34:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_file(char **file, char *str, t_stock **g_cmd, char **envp)
{
	size_t	i;
	int		j;
	int		len;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (*file)
		free(*file);
	len = ft_strlen(str + i);
	if (!(*file = malloc(len + 1)))
		return (MALL_ERR);
	j = -1;
	--i;
	while (str && str[++i])
		(*file)[++j] = str[i];
	(*file)[j + 1] = 0;
	parse_token(*file, file, g_cmd, envp);
	return (i);
}

int			set_file_name(t_stock **g_cmd, char *str, char **envp)
{
	int i;
	int fd;
	int ret;

	i = 0;
	errno = 0;
	fd = 0;
	if (str[i] == '<' && str[++i])
	{
		ret = parse_file(&(*g_cmd)->input, str + i, g_cmd, envp);
		if (errno == 0)
			fd = open((*g_cmd)->input, O_RDONLY);
		if (errno != 0)
		{
			write_error((*g_cmd)->input, ": ", strerror(errno), 1);
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);
	}
	else if (str[i] && str[++i])
	{
		if (str[i] == '>')
			++i;
		parse_file(&(*g_cmd)->output, str + i, g_cmd, envp);
		if (errno == 0 && i == 1)
		{
			(*g_cmd)->r_type = RIGHT;
			fd = open((*g_cmd)->output, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
			S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else if (errno == 0)
		{
			(*g_cmd)->r_type = D_RIGHT;
			fd = open((*g_cmd)->output, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
			S_IRGRP | S_IWGRP | S_IWUSR);
		}
		if (errno != 0)
		{
			write_error((*g_cmd)->output, ": ", strerror(errno), 1);
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);
	}
	return (-1);
}

int			parse_token(char *token, char **new, t_stock **g_cmd, char **envp)
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
			return (set_file_name(g_cmd, token + j, envp));
		else
			(*new)[k++] = token[j++];
		if (ret < 0)
			break ;
		j += ret;
	}
	(*new)[k] = 0;
	return (ret);
}

int			set_token(char **tokens, t_stock **g_cmd, char **envp)
{
	int	i;
	int	ret;
	int	k;

	k = 0;
	if (!((*g_cmd)->tokens = malloc((sizeof(char *) * (ft_tabsize(tokens) + 1)))))
	{
		ft_free(tokens);
		return (MALL_ERR);
	}
	i = -1;
	while (tokens[++i])
	{
		if ((ret = parse_token(tokens[i], &(*g_cmd)->tokens[k],
		g_cmd, envp)) < -1)
		{
			ft_free(tokens);
			(*g_cmd)->tokens[++k] = NULL;
			return (ret);
		}
		if (ret != -1)
			++k;
	}
	ft_free(tokens);
	(*g_cmd)->tokens[k] = NULL;
	return (0);
}
