/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:39:20 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 11:52:13 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Écrit l’integer n sur le file descriptor donné.
** suivi d'un retour à la ligne.
** =========
** #1 : l'entier à écrire.
** #2 : le file descriptor.
** =========
*/

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		n = 147483648;
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
