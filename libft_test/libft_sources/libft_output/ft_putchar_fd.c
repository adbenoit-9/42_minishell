/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:40:38 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:19 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Écrit le caractère c sur le file descriptor donné.
** =========
** #1 : le caractère à écrire.
** #2 : le file descriptor.
** =========
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
