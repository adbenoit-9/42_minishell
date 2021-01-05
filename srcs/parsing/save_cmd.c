/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/05 14:34:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_sep(char *str, int *i, int *quote)
{
	if (str[*i] == '\\')
			++(*i);
	else if (str[*i] == '\'' && *quote != 1)
		*quote = 1;
	else if (str[*i] == '\"' && *quote != 2)
		*quote = 2;
	else if (str[*i] == '\'' && *quote == 1)
		*quote = 0;
	else if (str[*i] == '\"' && *quote == 2)
		*quote = 0;
	else if (*quote == 0 && (str[*i] == ';' || str[*i] == '|'))
		return (1);
	if (!str[*i])
		--(*i);
	return (0);
}

static int	is_error(t_cmd *cmd)
{
	if (cmd->err >= -1)
		return (0);
	if (cmd->err == MALL_ERR)
		errno_msg(NULL, NULL, MALL_ERR);
	else if (cmd->err == QUOTE_NOT_FOUND)
		error_msg(NULL, NULL, "syntax error\n", 2);
	else
		return (0);
	return (cmd->err);
}

int			save_cmd(char *str, t_cmd **cmd, char *envp[])
{
	int		i;
	int		ret;
	char	**tokens;

	ret = 0;
	i = -1;
	while (str[++i])	
		if (is_cmd_sep(str, &i, &ret) == 1)
			break ;
	if (!(tokens = split_token(str, ' ', i)))
		(*cmd)->err = MALL_ERR;
	else
	{
		*cmd = ft_cmdnew(set_sep(str + i, &i));
		(*cmd)->err = set_token(tokens, cmd, envp);
	}
	ft_free(tokens);
	if ((ret = is_error(*cmd)) == 0)
		return (i);
	return (ret);
}
