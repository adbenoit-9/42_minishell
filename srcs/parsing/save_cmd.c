/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/20 23:52:13 by adbenoit         ###   ########.fr       */
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

static int	is_error(t_cmd *cmd)
{
	if (cmd->err >= -1)
		return (0);
	if (cmd->err == MALL_ERR)
		errno_msg(NULL, NULL, MALL_ERR);
	else if (cmd->err == QUOTE_NOT_FOUND)
		error_msg(NULL, NULL, "syntax error : quote expected\n", 258);
	else
		return (0);
	return (cmd->err);
}

int			save_cmd(char *str, t_cmd **cmd, char *envp[])
{
	size_t	i;
	int		ret;
	int		bs;
	char	**tokens;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		bs = 0;
		--i;
		while (str[++i] == '\\')
			++bs;
		ft_is_in_quote(str, i, &ret);
		if (bs % 2 == 0 && ret == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
	}
	if (!(tokens = split_token(str, ' ', i)))
		(*cmd)->err = MALL_ERR;
	else
	{
		*cmd = ft_cmdnew(set_sep(str + i, &i));
		(*cmd)->err = set_token(tokens, cmd, envp);
	}
	if ((ret = is_error(*cmd)) == 0)
		return (i);
	return (ret);
}
