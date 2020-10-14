/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:49:10 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/14 16:46:31 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_new_arg(char const *s, char c, size_t n, int quote)
{
	int ret;

	ret = 0;
	if (s[n] == c && quote == 0)
		ret = 1;
	if (ret == 1 && (n == 0 || (s[n - 1] != '\\' && s[n - 1] != c)))
		return (1);
	return (0);
}

static size_t	ft_countrow(char const *s, char c, size_t n)
{
	size_t	count;
	size_t	i;
	int		quote;

	count = 0;
	i = 0;
	quote = 0;
	if (s[0] && s[0] != c)
		count++;
	while (s[i] && i < n)
	{
		quote = is_in_quote(s, &i, quote);
		if (is_new_arg(s, c, i, quote) == 1)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_size(char const *s, char c, size_t i, size_t n)
{
	size_t	size;
	int		quote;
	int		tmp;

	size = 0;
	while (s[i] && i < n)
	{
		tmp = i;
		quote = is_in_quote(s, &i, quote);
		size += (i - tmp);
		if (is_new_arg(s, c, i, quote) == 1)
			break ;
		size++;
		i++;
	}
	return (size);
}

static void		*ft_free(char **tab, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char			**split_arg(char const *s, char c, size_t n)
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
			return (ft_free(tab, index[1]));
		index[2] = -1;
		while (++index[2] < size[1])
			tab[index[1]][index[2]] = s[index[0]++];
		tab[index[1]][index[2]] = 0;
	}
	tab[index[1]] = NULL;
	return (tab);
}
