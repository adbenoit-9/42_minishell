/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:17:19 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	print_c(char c, t_arg *format, size_t ret)
{
	if (format && format->flag != '-')
		ret += print_space(format, 1);
	ret += print_char(c);
	ret += print_space(format, 1);
	return (ret);
}
