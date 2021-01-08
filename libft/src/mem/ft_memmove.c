/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:53:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 02:03:28 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (i < len)
	{
		if (&((unsigned char *)dst)[0] < &((unsigned char *)src)[0])
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			++i;
		}
		else
		{
			((unsigned char *)dst)[i + len - 1] =
							((unsigned char *)src)[len - 1];
			--len;
		}
	}
	return (dst);
}
