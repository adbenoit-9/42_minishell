/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:13:12 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/30 23:30:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_file(t_list **file, char *str, t_cmd **cmd, char *envp[])
{
	int	i;
	int	ret;

	i = 0;
	ft_lstclear(file, free);
	if (!(*file = ft_lstnew(ft_strdup(str))) || !(*file)->content)
	{
		ft_lstclear(file, free);
		return (MALL_ERR);
	}
	if ((ret = parse_token(str, file, cmd, envp)) < -1)
		ft_lstclear(file, free);
	else if (ret == -1)
	{
		while (str[i] == ' ')
			++i;
		if ((ret = parse_token(str + i + 1, file, cmd, envp)) < -1)
			return (ret);
		error_msg("$", (*file)->content, ": ambiguous redirect\n", 127);
		ft_lstclear(file, free);
		return (FILE_ERR);
	}
	return (ret);
}

static int	open_output(t_cmd *cmd, int i)
{
	int	fd;

	fd = 0;
	if (errno == 0 && i == 1)
	{
		cmd->r_type = RIGHT;
		fd = open(cmd->output->content, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
		S_IRGRP | S_IWGRP | S_IWUSR);
	}
	else if (errno == 0)
	{
		cmd->r_type = D_RIGHT;
		fd = open(cmd->output->content, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR |
		S_IRGRP | S_IWGRP | S_IWUSR);
	}
	return (fd);
}

int			set_file_name(t_cmd **cmd, char *str, char *envp[])
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
		fd = (errno == 0) ? open((*cmd)->input->content, O_RDONLY) : 0;
		if (errno != 0)
			return (errno_msg(NULL, (*cmd)->input->content, FILE_ERR));
	}
	else if (str[i] == '>' && str[++i])
	{
		i = (str[i] == '>') ? i + 1 : i;
		if ((ret = parse_file(&(*cmd)->output, str + i, cmd, envp)) < 0)
			return (ret);
		if ((fd = open_output(*cmd, i)) < 0)
			return (errno_msg(NULL, (*cmd)->output->content, FILE_ERR));
	}
	if (fd != 0)
		close(fd);
	return (-1);
}
