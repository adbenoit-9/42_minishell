/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:06 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 17:23:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_change_shlvl(char ***envp)
{
	char	*value;
	int		nb;
	int		n;
	int		ret;

	n = 0;
	if (!(value = ft_getenv("SHLVL", &n, *envp)))
		return (ft_setenv("SHLVL", "1", 0, envp));
	nb = ft_atoi(value);
	if (nb < 0)
		return (ft_setenv("SHLVL", "0", 0, envp));
	else if (nb < 999)
	{
		value = ft_itoa(nb + 1);
		ret = ft_setenv("SHLVL", value, 0, envp);
		free(value);
		return (ret);
	}
	ft_putstr_fd("minishell: avertissement : niveau de shell trop élevé (1000), initialisation à 1\n", 2);
	return (ft_setenv("SHLVL", "1", 0, envp));
}
