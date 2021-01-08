/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:05:19 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/07 10:02:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(void *tab, int ret)
{
	free(tab);
	return (ret);
}

static char	*ft_getnb(const char *str, int *i)
{
	int		j;
	int		k;
	char	*nb;

	j = 0;
	k = *i - 1;
	while (str[++k] && str[k] >= '0' && str[k] <= '9')
		j++;
	if (!(nb = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
		nb[j++] = str[(*i)++];
	nb[j] = 0;
	return (nb);
}

char		ft_setflag(const char *str, int *i)
{
	char	ret;

	ret = ' ';
	if (str[*i] && str[*i] == '0')
		ret = '0';
	while (str[*i] && (str[*i] == '-' || str[*i] == '0'))
	{
		if (str[*i] == '-')
			ret = '-';
		++(*i);
	}
	return (ret);
}

int			ft_setwidth(va_list ap, t_arg *format, const char *str, int *i)
{
	char	*nb;
	int		nbr;

	if (str[*i] == '*')
	{
		++(*i);
		nbr = va_arg(ap, int);
		if (nbr < 0)
		{
			format->flag = '-';
			return (nbr * -1);
		}
		return (nbr);
	}
	if (!(nb = ft_getnb(str, i)))
		return (-2);
	if (nb[0] == 0)
		return (ft_free(nb, -1));
	nbr = ft_atoi(nb);
	return (ft_free(nb, nbr));
}

int			ft_setprec(const char *str, int *i, va_list ap)
{
	int		nbr;
	char	*nb;

	if (str[*i] == '.')
	{
		++(*i);
		if (str[*i] == '*')
		{
			++(*i);
			nbr = va_arg(ap, int);
			if (nbr < 0)
				nbr = -1;
			return (nbr);
		}
		if (!(nb = ft_getnb(str, i)))
			return (-2);
		nbr = ft_atoi(nb);
		if (nbr < 0)
			nbr = -1;
		return (ft_free(nb, nbr));
	}
	return (-1);
}
