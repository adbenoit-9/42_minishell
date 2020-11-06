/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/11/06 19:03:16 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_stock	*cmd;
	int		ret;
	size_t	i;

	(void)argc;
	(void)argv;
	erret = 0;
	while (1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, "\xF0\x9F\x90\x9A: ", 6);
		str = NULL;
		ret = get_next_line(0, &str);
		cmd = NULL;
		i = 0;
		while (str[i] == ' ')
			++i;
		if (parse_str(str + i) == 0)
		{
			parsing(str, &cmd, envp);
			ft_stockclear(&cmd, clear_one);
		}
		free(str);
		str = NULL;
	}
	return (0);
}
