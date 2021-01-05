/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:06 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 23:33:27 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_convert(const char *str)
{
	int i;
	int num;
	int neg;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (str[i])
		return (0);
	num = num * neg;
	return (num);
}

int			ft_incr_shlvl(char ***envp)
{
	char	*value;
	int		nb;
	int		n;
	int		ret;

	n = 0;
	if (!(value = ft_getenv("SHLVL", &n, *envp)))
		return (ft_setenv("SHLVL", "1", 0, envp));
	nb = ft_convert(value);
	if (nb < 0)
		return (ft_setenv("SHLVL", "0", 0, envp));
	else if (nb < 999)
	{
		value = ft_itoa(nb + 1);
		ret = ft_setenv("SHLVL", value, 0, envp);
		free(value);
		return (ret);
	}
	error_msg(NULL, "avertissement : ",
	"niveau de shell trop élevé (1000), initialisation à 1\n", 0);
	return (ft_setenv("SHLVL", "1", 0, envp));
}
