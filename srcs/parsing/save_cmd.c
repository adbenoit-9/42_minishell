/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/20 19:20:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_bs(char *str, size_t *i)
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

int				save_cmd(char *str, t_stock **cmd_lst, int cmd, char *envp[])
{
	size_t	i;
	size_t	tmp;
	int		k;
	int 	ret;
	t_stock	*new;

	new = ft_stocknew(cmd);
	k = 0;
	i = -1;
	while (str[++i])
	{
		tmp = i;
		k = is_in_quote(str, &tmp, k);
		i = k != 0 ? tmp : i;
		if (k == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
	}
	if (!(new->tokens = split_token(str, ' ', i)))
		ft_error(cmd_lst);
	i += set_sep(str + i, &(new->sep));
	new->err = set_token(new->tokens, &new, envp);
	if ((ret = parse_error(&new, cmd_lst)) == 0)
		ft_stockadd_back(cmd_lst, new);
	if (ret == 0 && str[i])
			return (parsing(str + i, cmd_lst, envp));
	return (0);
}
