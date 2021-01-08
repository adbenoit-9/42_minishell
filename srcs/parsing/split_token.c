/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:50:26 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 13:58:06 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_new_arg(char const *s, char c, int n, int g_quote)
{
	int	bs;
	int i;
	int	ret;

	bs = 0;
	i = n;
	ret = 0;
	while (i != 0 && s[--i] == '\\')
		++bs;
	if (bs % 2 != 0 || g_quote != 0)
		return (0);
	if (s[n] == c && (n == 0 || s[n - 1] != c))
		ret = 1;
	while (s[n] == c)
		++n;
	if (s[n] == '>' || s[n] == '<')
		ret = 0;
	return (ret);
}

static int	is_redirect(char const *s, int *i, int r, int n)
{
	int	bs;

	bs = 0;
	--(*i);
	while (s[++(*i)] == '\\')
		++bs;
	if (*i == n)
	{
		--(*i);
		return (0);
	}
	is_in_quote(s, *i - bs, &g_quote);
	if (g_quote == 0 && bs % 2 == 0 && (s[*i] == '<' || s[*i] == '>') && r == 0)
		return (1);
	return (0);
}

static int	ft_countrow(char const *s, char c, int n)
{
	int	count;
	int	i;
	int	r;

	count = 0;
	i = 0;
	g_quote = 0;
	r = 0;
	if (s[0] && s[0] != c)
		++count;
	while (i < n && s[i])
	{
		while (r == 1 && (s[i] == c || s[i] == '>'))
			++i;
		r = is_redirect(s, &i, r, n);
		if (ft_is_new_arg(s, c, i, g_quote) == 1 || r == 1)
			count++;
		++i;
	}
	if (i > 0 && s[i - 1] == c)
		--count;
	return (count);
}

static int	ft_size(char const *s, char c, int i, int n)
{
	int	size[2];
	int	r;

	size[0] = 0;
	r = 0;
	g_quote = 0;
	if (s[i] == '>' || s[i] == '<')
	{
		size[0] = (s[i + 1] == '>') ? 2 : 1;
		i += size[0] - 1;
		while (s[++i] == c)
			++size[0];
	}
	while (i < n && s[i])
	{
		size[1] = i;
		r = is_redirect(s, &i, r, n);
		size[0] += (i - size[1]);
		if (ft_is_new_arg(s, c, i, g_quote) == 1 || r == 1)
			break ;
		++size[0];
		++i;
	}
	return (size[0]);
}

char		**split_token(char const *s, char c, int n)
{
	char	**tab;
	int		index[3];
	int		size[2];

	if (s == NULL)
		return (NULL);
	index[0] = 0;
	index[1] = -1;
	size[0] = ft_countrow(s, c, n);
	if (!(tab = malloc(sizeof(char *) * (size[0] + 1))))
		return (NULL);
	while (++index[1] < size[0])
	{
		while (s[index[0]] == c)
			++index[0];
		size[1] = ft_size(s, c, index[0], n);
		if (!(tab[index[1]] = malloc(size[1] + 1)))
			return (ft_freetab(tab));
		ft_strncpy(tab[index[1]], s + index[0], size[1]);
		tab[index[1]][size[1]] = 0;
		index[0] += size[1];
	}
	tab[index[1]] = NULL;
	return (tab);
}
