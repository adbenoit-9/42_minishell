/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:44:13 by adbenoit          #+#    #+#             */
/*   Updated: 2021/01/08 15:29:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reset_buf(char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		++i;
	++i;
	j = 0;
	while (buf[i])
	{
		buf[j] = buf[i];
		++i;
		++j;
	}
	buf[j] = 0;
}

static int	ft_set_line(char *buf, size_t *len, t_list **lst)
{
	size_t	i;
	char	*str;
	t_list	*new;

	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		++(*len);
		++i;
	}
	str = ft_strndup(buf, i);
	if (str == NULL)
		return (-1);
	new = ft_lstnew(str);
	if (new == NULL)
	{
		free(str);
		return (-1);
	}
	ft_lstadd_back(lst, new);
	if (buf[i] == '\n')
		return (1);
	return (0);
}

static int	ft_put_line(t_list **lst, char **line, size_t len)
{
	t_list	*tmp;
	size_t	i;

	*line = (char *)malloc(len + 1);
	if (*line == NULL)
		return (-1);
	i = 0;
	while (i < len + 1)
	{
		(*line)[i] = 0;
		++i;
	}
	tmp = *lst;
	while (tmp)
	{
		ft_strcat(*line, tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static int	ft_get_line(char **line, t_gnl *gnl, t_list **lst, char *buf)
{
	long int	ret;
	int			status;

	ret = read(gnl->fd, buf, BUFFER_SIZE);
	buf[ret] = 0;
	while (ret == BUFFER_SIZE)
	{
		status = ft_set_line(buf, &gnl->len, lst);
		if (status == -1)
			return (-1);
		if (status == 1)
			break ;
		ret = read(gnl->fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
	}
	if (ret < BUFFER_SIZE)
		status = ft_set_line(buf, &gnl->len, lst);
	if (status == 0)
	{
		ft_put_line(lst, line, gnl->len);
		buf[0] = 0;
	}
	return (status);
}

int			get_next_line(int fd, char **line)
{
	t_gnl			gnl;
	static char		buf[BUFFER_SIZE + 1];
	t_list			*lst;
	int				status;

	gnl.len = 0;
	gnl.fd = fd;
	lst = NULL;
	if (gnl.fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	status = ft_set_line(buf, &gnl.len, &lst);
	if (status == 0)
		status = ft_get_line(line, &gnl, &lst, buf);
	if (status == 1)
	{
		ft_reset_buf(buf);
		status = ft_put_line(&lst, line, gnl.len);
	}
	ft_lstclear(&lst, free);
	return (status);
}
