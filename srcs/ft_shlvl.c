/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:06 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 16:43:34 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_incr_shlvl(char ***envp)
{
	char	*value;
	int		nb;
	int		n;

	n = 0;
	if (!(value = ft_getenv("SHLVL", &n, *envp)))
		return (ft_setenv("SHLVL", "1", 0, envp));
	nb = ft_atoi(value);
	if (nb < 0)
		return (ft_setenv("SHLVL", "0", 0, envp));
	else if (nb < 999)
		return (ft_setenv("SHLVL", ft_itoa(nb + 1), 0, envp));
	return (ft_setenv("SHLVL", "", 0, envp));
}
