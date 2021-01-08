/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:47:00 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:01:11 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istype(char c)
{
	if (c == NUM1 || c == NUM2 || c == HEX1 || c == HEX2 || c == STR || c == PTR
									|| c == CHAR || c == UN_INT || c == '%')
		return (1);
	return (0);
}

static int	ft_setarg(const char *str, va_list ap, t_arg *format, int *i)
{
	if (str[*i] && str[*i + 1] && str[*i] == '%')
	{
		++(*i);
		format->flag = ft_setflag(str, i);
		format->width = ft_setwidth(ap, format, str, i);
		format->prec = ft_setprec(str, i, ap);
		if (format->width == -2 || format->prec == -2)
			return (-1);
		format->type = str[*i];
	}
	return (0);
}

int			ft_printf(const char *str, ...)
{
	int		i;
	size_t	ret;
	t_arg	format;
	va_list	ap;

	va_start(ap, str);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '%')
		{
			if (ft_setarg(str, ap, &format, &i) == -1)
				return (-1);
			if (ft_istype(format.type) == 0)
				return (-1);
			ret = print_arg(ap, &format, ret);
		}
		else
			ret += print_char(str[i]);
		++i;
	}
	va_end(ap);
	return (ret);
}
