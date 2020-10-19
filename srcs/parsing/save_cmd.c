/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 18:18:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char		*get_unknow_cmd(char *cmd, int k, char *str, size_t *i)
// {
// 	int		len;

// 	len = 0;
// 	if (k == UNKNOW)
// 	{
// 		while (str[len + *i] && ft_isspace(str[len + *i]) == 0)	
// 			++len;
// 		cmd = ft_strndup(str + *i, len);
// 		(*i) += len;
// 		while (ft_isspace(str[*i]) == 1)
// 			++(*i);
// 	}
// 	return (cmd);
// }

// static void		add_unknow_cmd(char *tokens, char **new_tokens, char *cmd)
// {
// 	if (cmd)
// 	{
// 		tokens = ft_strdup(*new_tokens);
// 		if (tokens && tokens[0])
// 		{
// 			cmd = ft_strjoin(cmd, " ");
// 			*new_tokens = ft_strjoin(cmd, tokens);
// 		}
// 		else
// 			*new_tokens = ft_strdup(cmd);
// 		free(cmd);
// 		free(tokens);
// 	}
// }

// static size_t	tokens_len(char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len] && str[len] != '\n')
// 		++len;
// 	return (len);
// }

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
		ft_deal_error(cmd_lst, &new, str + i);
	if (str[i])
		return (parsing(str + i, cmd_lst, envp));
	else
		return (0);
}
