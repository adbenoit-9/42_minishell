/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/09 15:34:57 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_bs(char *str, size_t *i)
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

static int	is_error(t_stock *cmd)
{
	if (cmd->err >= -1)
		return (0);
	if (cmd->err == MALL_ERR)
		print_error(NULL, strerror(errno), "\n", 1);
	else if (cmd->err == QUOTE_NOT_FOUND)
		print_error(NULL, NULL, "syntax error : quote expected\n", 258);
	else
		return (0);
	return (cmd->err);
}

int			save_cmd(char *str, t_stock **cmd, char *envp[])
{
	size_t	i;
	int		ret;
	char	**tokens;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		i = is_in_quote(str, i, &ret);
		if (ret == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
	}
	if (!(tokens = split_token(str, ' ', i)))
		return (print_errno(NULL, NULL, MALL_ERR));
	*cmd = ft_stocknew(set_sep(str + i, &i));
	(*cmd)->err = set_token(tokens, cmd, envp);
	if ((ret = is_error(*cmd)) == 0)
		return (i);
	return (ret);
}
