/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:49:10 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 15:35:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_new_arg(char const *s, char c, unsigned int n, int quote)
{
	int ret;

	ret = 0;
	if (s[n] == c && quote == 0)
		ret = 1;
	if (ret == 1 && (n == 0 || (s[n - 1] != '\\' && s[n - 1] != c)))
		return (1);
	return (0);
}
int				is_in_quote(char const *s, unsigned int i, int quote)
{
	if (s[i] == '\'' || s[i] == '\"')
	{
		if (quote != 0 && s[i - 1] == '\\')
			return (quote);
		else if (s[i] == '\'' && quote == 0)
			return (1);
		else if (s[i] == '\"' && quote == 0)
			return (2);
		else if (quote == 1 && s[i] == '\'')
			return (0);
		else if (quote == 2 && s[i] == '\"' && s[i - 1] != '\\')
			return (0);
	}
	return (quote);
}

unsigned int	ft_countrow(char const *s, char c, unsigned int n)
{
	unsigned int	count;
	unsigned int	i;
	int				quote;

	count = 0;
	i = 0;
	quote = 0;
	if (s[0] && s[0] != c)
		count++;
	while (s[i] && i < n)
	{
		quote = is_in_quote(s, i , quote);
		if (is_new_arg(s, c, i, quote) == 1)
			count++;
		i++;
	}
	return (count);
}

unsigned int	ft_size(char const *s, char c, unsigned int i, unsigned int n)
{
	unsigned int	size;
	int				quote;

	size = 0;
	while (s[i] && i < n)
	{
		quote = is_in_quote(s, i , quote);
		if (is_new_arg(s, c, i, quote) == 1)
			break ;
		size++;
		i++;
	}
	return (size);
}

void			*ft_free(char **tab, unsigned int k)
{
	unsigned int	i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char			**split_arg(char const *s, char c, unsigned int n)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	size[2];

	if (s == NULL || n == 0)
		return (NULL);
	i = 0;
	k = -1;
	size[0] = ft_countrow(s, c, n);
	if (!(tab = malloc(sizeof(char *) * (size[0] + 1))))
		return (0);
	while (++k < size[0])
	{
		while (s[i] == c && s[i])
            i++;
		size[1] = ft_size(s, c, i, n);
		if (!(tab[k] = malloc(size[1] + 1)))
			return (ft_free(tab, k));
		j = -1;
		while (++j < size[1])
			tab[k][j] = s[i++];
		tab[k][j] = 0;
	}
	tab[k] = NULL;
	return (tab);
}
