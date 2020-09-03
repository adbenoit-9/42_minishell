/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:27:21 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/12 14:47:38 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include "libft.h"

/*
** PROTOTYPE
*/

char		*ft_strjoin_gnl(char *s1, char *s2);
ssize_t		ft_search_line(char *s);

void		ft_reinit_buffer(ssize_t start, char *buffer);
char		*ft_create_line(char *str, char **line);
int	    	ft_get_line(char **line, char *buffer, int ret_search, int ret_read);
int			get_next_line(int fd, char **line);

#endif
