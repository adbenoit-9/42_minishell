/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:31:39 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			print_in_format(unsigned int n, t_arg *format, size_t len,
char *base)
{
	size_t	ret;
	int		k;

	ret = 0;
	while (format->flag == '0' && format->width > (int)len && format->prec < 0)
	{
		ret += print_char('0');
		format->width--;
	}
	k = format->prec + 1;
	while (--k > (int)len)
		ret += print_char('0');
	ret += ft_putnbr_base(n, len, base);
	return (ret);
}

size_t			ft_putnbr_base(unsigned int n, size_t len, char *base)
{
	size_t	baselen;

	if (n == 0)
		ft_putchar_fd('0', 1);
	baselen = ft_strlen(base);
	if (n > 0)
	{
		if (n / baselen != 0)
			ft_putnbr_base(n / baselen, len, base);
		ft_putchar_fd(base[n % baselen], 1);
	}
	return (len);
}

static size_t	ft_arglen_base(unsigned int n, size_t baselen)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / baselen;
		len++;
	}
	return (len);
}

size_t			print_ux(unsigned int n, t_arg *format, size_t ret, char *base)
{
	size_t	len;
	size_t	baselen;

	baselen = ft_strlen(base);
	len = ft_arglen_base(n, baselen);
	if (format->flag != '-' && (format->prec > -1 || format->flag != '0'))
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
		ret += print_in_format(n, format, len, base);
	ret += print_space(format, len);
	return (ret);
}
