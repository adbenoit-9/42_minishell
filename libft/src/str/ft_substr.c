/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:09:00 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 16:05:11 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start - 1)
	{
		if (!(str = malloc(sizeof(char) * (ft_strlen(s) - start + 1))))
			return (NULL);
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		++i;
		++start;
	}
	str[i] = 0;
	return (str);
}
