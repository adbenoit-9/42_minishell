/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:06 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 19:01:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_incr_shlvl(char ***envp)
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
	error_msg(NULL, "avertissement : ",
	"niveau de shell trop élevé (1000), initialisation à 1\n", 0);
	return (ft_setenv("SHLVL", "1", 0, envp));
}
