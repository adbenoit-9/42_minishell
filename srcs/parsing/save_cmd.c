/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/27 13:39:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_bs(char *str, size_t *i)
{
	size_t	n;

	n = 0;
	while (str[n + *i] == '\\')
		++n;
	(*i) += n;
	if ((n % 2) == 0)
		return (0);
	return (1);
}

size_t	ft_size_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		++i;
	return (i);
}

int		save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[])
{
	size_t	i;
	size_t	tmp;
	int		ret;
	char	**tokens;
	t_stock	*new;

	new = ft_stocknew(cmd);
	ret = 0;
	i = -1;
	while (str[++i])
	{
		tmp = i;
		ret = is_in_quote(str, &tmp, ret);
		i = ret != 0 ? tmp : i;
		if (ret == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
	}
	if (!(tokens = split_token(str, ' ', i)))
		return (MALL_ERR);
	if (!(new->tokens = malloc((sizeof(char *) * (ft_size_tab(tokens) + 1)))))
		return (MALL_ERR);
	i += set_sep(str + i, &(new->sep));
	new->err = set_token(tokens, &new, envp);
	if ((ret = parse_error(&new, cmd_lst)) == 0)
		ft_stockadd_back(cmd_lst, new);
	if (ret == 0 && str[i])
		return (parsing(str + i, cmd_lst, envp));
	return (0);
}
