/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:35:36 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arglen(int n)
{
	size_t	num;
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		len++;
		num = -n;
	}
	else
		num = n;
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static size_t	ft_putsign(int n)
{
	size_t	num;

	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		num = n * -1;
	}
	else
		num = n;
	return (num);
}

size_t			print_d(int n, t_arg *format, size_t ret)
{
	size_t	num;
	size_t	len;

	len = ft_arglen(n);
	if (n < 0 && format->prec > 0)
		++format->prec;
	if (format && format->flag != '-' && (format->prec > -1 ||
	format->flag != '0'))
	{
		format->flag = ' ';
		ret += print_space(format, len);
	}
	if (n == 0 && format->prec == 0)
	{
		if (format->width > 0)
			ret += print_char(' ');
	}
	else
	{
		num = ft_putsign(n);
		ret += print_in_format(num, format, len, "0123456789");
	}
	ret += print_space(format, len);
	return (ret);
}
