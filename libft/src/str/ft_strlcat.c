/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:20:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 01:53:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = ft_strlen(dst);
	k = i;
	l = ft_strlen(src);
	j = 0;
	while (src[j] && i < dstsize - 1 && dstsize)
		dst[i++] = src[j++];
	if (dstsize > k)
	{
		dst[i] = 0;
		return (l + k);
	}
	else
		return (l + dstsize);
}
