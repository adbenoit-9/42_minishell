/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/08/25 17:01:04 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A};
	char buffer[4098];

	write(1, "\033[1;45mLesPetitsCoquillages", 27);
	write(1, shell, 4);
	write(1, ":\033[0m ", 4);
	read(0, buffer, 4098);
}
