/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:50:26 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/16 02:03:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_is_new_arg(char const *s, char c, size_t n, int quote)
{
	int	bs;
	int i;
	int	ret;

	bs = 0;
	i = n;
	ret = 0;
	while (s[--i] == '\\')
		++bs;
	if (bs % 2 != 0 || quote != 0)
		return (0);
	if (s[n] == c)
		ret = 1;
	while (s[n] == c)
		++n;
	if (s[n] == '>' || s[n] == '<')
		ret = 0;
	return (ret);
}

static	int ft_is_redirect(char const *s, int quote, size_t *i, int r)
{
	int	bs;

	bs = 0;
	--(*i);
	while (s[++(*i)] == '\\')
		++bs;
	if (quote == 0 && bs % 2 == 0 && (s[*i] == '<' || s[*i] == '>') && r == 0)
		return (1);
	return (0);
}

static size_t	ft_countrow(char const *s, char c, size_t n)
{
	size_t	count;
	size_t	i;
	int		quote;
	int		r;

	count = 0;
	i = 0;
	quote = 0;
	r = 0;
	if (s[0] && s[0] != c)
		++count;
	while (i < n && s[i])
	{
		while (r == 1 && (s[i] == c || s[i] == '>'))
			++i;
		ft_is_in_quote(s, i, &quote);
		r = ft_is_redirect(s, quote, &i, r);
		if (ft_is_new_arg(s, c, i, quote) == 1 || r == 1)
			count++;
		++i;
	}
	if (i > 0 && s[i - 1] == c)
		--count;
	return (count);
}

static size_t	ft_size(char const *s, char c, size_t i, size_t n)
{
	size_t	size;
	int		quote;
	int		tmp;
	int		r;

	size = 0;
	r = 0;
	quote = 0;
	if (s[i] == '>' || s[i] == '<')
	{
		++size;
		if (s[i + 1] == '>')
		{
			++i;
			++size;
		}
		while (s[++i] == c)
			++size;
	}
	while (i < n && s[i])
	{
		tmp = i;
		ft_is_in_quote(s, i, &quote);
		r = ft_is_redirect(s, quote, &i, r);
		size += (i - tmp);
		if (ft_is_new_arg(s, c, i, quote) == 1 || r == 1)
			break ;
		++size;
		++i;
	}
	return (size);
}

char			**split_token(char const *s, char c, size_t n)
{
	char	**tab;
	size_t	index[3];
	size_t	size[2];

	if (s == NULL)
		return (NULL);
	index[0] = 0;
	index[1] = -1;
	size[0] = ft_countrow(s, c, n);
	if (!(tab = malloc(sizeof(char *) * (size[0] + 1))))
		return (0);
	while (++index[1] < size[0])
	{
		while (s[index[0]] == c)
			index[0]++;
		size[1] = ft_size(s, c, index[0], n);
		if (!(tab[index[1]] = malloc(size[1] + 1)))
			return (ft_free(tab));
		ft_strncpy(tab[index[1]], s + index[0], size[1]);
		tab[index[1]][size[1]] = 0;
		index[0] += size[1];
	}
	tab[index[1]] = NULL;
	return (tab);
}
