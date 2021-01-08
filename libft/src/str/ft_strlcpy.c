/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:40:57 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 01:58:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	j = 0;
	while (src[j] != 0)
		++j;
	i = 0;
	if (dstsize == 0)
		return (j);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	if (dstsize > 0)
		dest[i] = '\0';
	return (j);
}
