/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:30:49 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/06 01:58:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
	{
		str[j] = s1[i];
		++i;
		++j;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		++i;
		++j;
	}
	str[j] = 0;
	return (str);
}
