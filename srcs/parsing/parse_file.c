/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:13:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/08 00:34:38 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_file(char **file, char *str, t_stock **cmd, char **envp)
{
	size_t	i;
	int		ret;

	i = 0;
	if (*file)
		free(*file);
	if ((ret = parse_token(str, file, cmd, envp)) < -1)
		return (ret);
	if (ret == -1)
	{
        while (str[i] == ' ')
            ++i;
		if ((ret = parse_token(str + i + 1, file, cmd, envp)) < -1)
			return (ret);
		print_error("$", *file, ": ", 1);
		write(1, "ambiguous redirect\n", 19);
		free(*file);
		*file = NULL;
		return (FILE_ERR);
	}
	return (ret);
}

static int	open_output(t_stock *cmd, int i)
{
	int	fd;

	fd = 0;
	if (errno == 0 && i == 1)
	{
		cmd->r_type = RIGHT;
		fd = open(cmd->output, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
		S_IRGRP | S_IWGRP | S_IWUSR);
	}
	else if (errno == 0)
	{
		cmd->r_type = D_RIGHT;
		fd = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
		S_IRGRP | S_IWGRP | S_IWUSR);
	}
	return (fd);
}

int			set_file_name(t_stock **cmd, char *str, char **envp)
{
	int i;
	int fd;
	int ret;

	i = 0;
	fd = 0;
	if (str[i] == '<' && str[++i])
	{
		if ((ret = parse_file(&(*cmd)->input, str + i, cmd, envp)) < 0)
			return (ret);
		if (errno == 0)
			fd = open((*cmd)->input, O_RDONLY);
		if (errno != 0)
			return (print_errno(NULL, (*cmd)->input, FILE_ERR));
	}
	else if (str[i] == '>' && str[++i])
	{
		i = (str[i] == '>') ? i + 1 : i;
		if ((ret = parse_file(&(*cmd)->output, str + i, cmd, envp)) < 0)
			return (ret);
		if ((fd = open_output(*cmd, i)) < 0)
			return (print_errno(NULL, (*cmd)->output, FILE_ERR));
	}
	if (fd != 0)
		close(fd);
	return (-1);
}
