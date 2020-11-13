/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:50:26 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/12 17:49:31 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_new_arg(char const *s, char c, size_t n, int quote)
{
	int ret;

	ret = 0;
	if ((s[n] == c || s[n] == '<' || s[n] == '>') && quote == 0)
		ret = 1;
	if (ret == 1 && (n == 0 || (s[n - 1] != '\\' && s[n - 1] != c)))
		return (1);
	return (0);
}

static int		is_redirec(char const *s, size_t *i, int quote, int r)
{
	int	bs;

	bs = 0;
	--(*i);
	while (s[++(*i)] == '\\')
		++bs;
	if (quote == 1)
		return (r);
	if (bs % 2 == 0 && (s[*i] == '<' || s[*i] == '>') && r == 0)
	{
		if (s[*i] == '>' && s[*i + 1] == '>')
			++(*i);
		++(*i);
		while (s[*i] == ' ')
			++(*i);
		--(*i);
		return (1);
	}
	else if (r == 1)
	{
		if (bs % 2 == 0 && (s[*i] == '<' || s[*i] == '>' || s[*i] == ' ')
		&& quote == 0)
			return (0);
	}
	return (r);
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
		quote = is_in_quote(s, &i, quote);
		r = is_redirec(s, &i, quote, r);
		if (r != 1 && is_new_arg(s, c, i, quote) == 1)
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
	while (i < n && s[i])
	{
		tmp = i;
		quote = is_in_quote(s, &i, quote);
		r = is_redirec(s, &i, quote, r);
		size += (i - tmp);
		if (r != 1 && is_new_arg(s, c, i, quote) == 1)
			break ;
		size++;
		i++;
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
		while (s[index[0]] == c && s[index[0]])
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
