/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:18:59 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ptrlen(unsigned long int n, size_t baselen)
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

static size_t	ft_putptr(unsigned long int n, size_t len, char *base)
{
	size_t	baselen;

	if (n == 0)
		ft_putchar_fd('0', 1);
	baselen = ft_strlen(base);
	if (n > 0)
	{
		if (n / baselen != 0)
			ft_putptr(n / baselen, len, base);
		ft_putchar_fd(base[n % baselen], 1);
	}
	return (len);
}

size_t			print_p(unsigned long int n, t_arg *format, size_t ret,
char *base)
{
	size_t	len;
	int		k;

	len = ft_ptrlen(n, ft_strlen(base)) + 2;
	if (format->flag == ' ')
		ret += print_space(format, len);
	if (n == 0 && format->prec == 0)
		;
	else
	{
		while (format->flag == '0' && format->width > (int)len
		&& format->prec == -1)
		{
			ret += print_char('0');
			format->width--;
		}
		k = format->prec + 1;
		while (--k > (int)len)
			ret += print_char('0');
		ft_putstr_fd("0x", 1);
		ret += ft_putptr(n, len, base);
	}
	ret += print_space(format, len);
	return (ret);
}
