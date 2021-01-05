/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:24:02 by mabriand          #+#    #+#             */
/*   Updated: 2019/12/12 14:47:14 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/get_next_line.h"

/*
** Réinitialise un buffer en supprimant les caractères avant '\n' inclu.
** =========
** #1 : la position de '\n' dans le buffer ou -1 s'il n'y est pas.
** #2 : un buffer.
** =========
*/

void	ft_reinit_buffer(ssize_t pos_end_line, char *buffer)
{
	size_t	i;
	ssize_t	start_new_line;

	i = 0;
	start_new_line = pos_end_line + 1;
	while (buffer[start_new_line] != '\0')
	{
		buffer[i] = buffer[start_new_line];
		start_new_line++;
		i++;
	}
	buffer[i] = '\0';
}

/*
** Applique ft_strjoin à deux chaînes de caractères s et line
** pour en obtenir une nouvelle. Si s est une chaîne nulle
** la fonction copie str.
** =========
** #1 : une chaîne de caractères.
** #2 : un pointeur sur une chaîne de caractères.
** =========
** Retourne la chaîne de caractères résultante.
*/

char	*ft_create_line(char *str, char **line)
{
	size_t	len;
	char	*s;

	s = *line;
	len = ft_strlen(str);
	if (s == NULL)
		s = ft_strndup(str, len);
	else
		s = ft_strjoin_gnl(s, str);
	return (s);
}

/*
** Si ft_search_line retourne la position d'un \n' dans le buffer,
** la fonction copie la fin de la ligne courante dans tmp,
** la supprime du buffer, puis rempli line en appliquand ft_create_line.
** Sinon elle rempli directement line.
** =========
** #1 : un pointeur sur une chaine de caractères.
** #2 : un buffer pour read().
** #3 : la position de '\n' dans le buffer ou -1 s'il n'y est pas.
** #4 : le nbr d'octets lus par read().
** =========
** Retourne 1 si on est arrivé à la fin d'une ligne, 0 sinon.
*/

int		ft_get_line(char **line, char *buffer, int ret_search, int ret_read)
{
	char	*tmp;

	buffer[ret_read] = '\0';
	if (ret_search >= 0)
	{
		tmp = ft_strndup(buffer, ret_search);
		*line = ft_create_line(tmp, line);
		ft_reinit_buffer(ret_search, buffer);
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_create_line(buffer, line);
		return (0);
	}
}

/*
** Renvoie une ligne lue depuis un descripteur de fichier,
** sans le retour à la ligne.
** =========
** #1 : le fd donné par open().
** #2 : un pointeur sur une chaîne de caractères.
** =========
** Retourne 1 si une ligne a été lue, 0 si l'EOF a été atteint,
** -1 si une erreur est survenue.
*/

int		get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		ret_read;
	ssize_t		ret_search;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup(buffer);
	if ((ret_search = ft_search_line(buffer)) >= 0)
	{
		free(*line);
		(*line) = ft_strndup(buffer, ret_search);
		ft_reinit_buffer(ret_search, buffer);
		return (1);
	}
	while ((ret_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		ret_search = ft_search_line(buffer);
		if (ft_get_line(line, buffer, ret_search, ret_read) == 1)
			return (1);
	}
	if (ret_read == 0)
		return (0);
	return (-1);
}
