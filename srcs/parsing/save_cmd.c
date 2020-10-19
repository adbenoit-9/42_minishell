/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 19:41:32 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_error(t_stock **new, t_stock **cmd_lst, char *str)
{
	if ((*new)->err == SEP_ERR)
		free(*new);
	(*cmd_lst)->err = 0;
	(void)str;
	return (0);
}

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
	i += set_sep(str + i, &new);
	new->err = set_token(new->tokens, &new, envp);
	if (new->err == 0)
	{
		set_token(new->input, &new, envp);
		set_token(new->output, &new, envp);
		ft_stockadd_back(cmd_lst, new);
	}
	else
		parse_error(cmd_lst, &new, str + i);
	if (str[i])
		return (parsing(str + i, cmd_lst, envp));
	else
		return (0);
}
