/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:49:10 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/13 16:35:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_countrow(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	i = 0;
	if (s[0] != c && s[0] != 0)
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

unsigned int	ft_size(char const *s, char c, unsigned int i)
{
	unsigned int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
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

char			**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (s == NULL)
		return (NULL);
	i = 0;
	k = -1;
	if (!(tab = malloc(sizeof(char*) * (ft_countrow(s, c) + 1))))
		return (0);
	while (++k < ft_countrow(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (!(tab[k] = malloc(sizeof(char) * (ft_size(s, c, i) + 1))))
			return (ft_free(tab, k));
		j = -1;
		i--;
		while (s[++i] != c && s[i])
			tab[k][++j] = s[i];
		tab[k][j + 1] = 0;
	}
	tab[k] = 0;
	return (tab);
}
