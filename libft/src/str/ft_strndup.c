/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 03:04:54 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 16:04:56 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && i < n)
		++i;
	if (!(copy = malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strncpy(copy, s1, i);
	copy[i] = '\0';
	return (copy);
}
