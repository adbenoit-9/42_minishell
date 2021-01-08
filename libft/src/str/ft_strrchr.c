/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:15:41 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 02:02:49 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	if ((char)c == '\0')
		return ((char *)s + i);
	while (i > 0 && ((char *)s)[i] != (char)c)
		--i;
	if (((char *)s)[i] != (char)c)
		return (NULL);
	return ((char *)s + i);
}
