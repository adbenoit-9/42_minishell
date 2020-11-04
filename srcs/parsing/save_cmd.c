/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/04 19:40:24 by adbenoit         ###   ########.fr       */
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

int		save_cmd(char *str, t_stock **cmd_lst, char *envp[])
{
	size_t	i;
	size_t	tmp;
	int		ret;
	char	**tokens;

	*cmd_lst = ft_stocknew(UNKNOW);
	ret = 0;
	i = -1;
	while ((*cmd_lst)->err == 0 && str[++i])
	{
		tmp = i;
		ret = is_in_quote(str, &tmp, ret);
		i = ret != 0 ? tmp : i;
		if (ret == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
		if (!str[i])
			(*cmd_lst)->err = ALONE_BS;
	}
	if (!(tokens = split_token(str, ' ', i)))
		return (MALL_ERR);
	if (!((*cmd_lst)->tokens = malloc((sizeof(char *) * (ft_size_tab(tokens) + 1)))))
		return (MALL_ERR);
	i += set_sep(str + i, &((*cmd_lst)->sep));
	if ((*cmd_lst)->err == 0)
		(*cmd_lst)->err = set_token(tokens, cmd_lst, envp);
	if ((ret = parse_error(cmd_lst, cmd_lst)) == 0)
		return (i);
	return (ret);
}
