/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:07:18 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	print_space(t_arg *format, size_t len)
{
	size_t	ret;
	char	flag;

	ret = 0;
	flag = format->flag;
	if (format->flag == '-')
		flag = ' ';
	if ((format->type == STR && format->prec > (int)len) ||
	format->type == CHAR || format->type == '%')
		format->prec = -1;
	while (format->width > format->prec && (format->width > (int)len ||
	(format->type == STR && format->prec > -1)))
	{
		ret += print_char(flag);
		format->width--;
	}
	return (ret);
}

size_t	print_arg(va_list ap, t_arg *format, size_t ret)
{
	static char	*base_x = "0123456789abcdef";
	static char	*base_ux = "0123456789ABCDEF";

	if (format->type == NUM1 || format->type == NUM2)
		ret = print_d(va_arg(ap, int), format, ret);
	else if (format->type == UN_INT)
		ret = print_ux(va_arg(ap, unsigned int), format, ret, "0123456789");
	else if (format->type == HEX1)
		ret = print_ux(va_arg(ap, unsigned int), format, ret, base_x);
	else if (format->type == HEX2)
		ret = print_ux(va_arg(ap, unsigned int), format, ret, base_ux);
	else if (format->type == CHAR)
		ret = print_c((unsigned char)va_arg(ap, int), format, ret);
	else if (format->type == STR)
		ret = print_s(va_arg(ap, char *), format, ret);
	else if (format->type == PTR)
		ret = print_p(va_arg(ap, unsigned long int), format, ret, base_x);
	else if (format->type == '%')
		ret = print_c('%', format, ret);
	return (ret);
}
