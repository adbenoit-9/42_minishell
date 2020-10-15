/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/15 17:04:33 by adbenoit         ###   ########.fr       */
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

// static void		add_unknow_cmd(char *input, char **new_input, char *cmd)
// {
// 	if (cmd)
// 	{
// 		input = ft_strdup(*new_input);
// 		if (input && input[0])
// 		{
// 			cmd = ft_strjoin(cmd, " ");
// 			*new_input = ft_strjoin(cmd, input);
// 		}
// 		else
// 			*new_input = ft_strdup(cmd);
// 		free(cmd);
// 		free(input);
// 	}
// }

// static size_t	input_len(char *str)
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
		if (k == 0 && is_bs(str, &i) == 0 && ft_issep(str[i], 0) == 1)
			break ;
	}
	if (!(new->input = split_arg(str, ' ', i)))
		ft_error(cmd_lst);
	i += set_sep(str + i, &new);
	set_input(new->input, &new, envp);
	ft_stockadd_back(cmd_lst, new);
	if (str[i])
		return (parsing(str + i, cmd_lst, envp));
	else
		return (0);
}
