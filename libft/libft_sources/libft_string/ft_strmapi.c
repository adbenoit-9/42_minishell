/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:57:40 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/28 12:00:46 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_header/libft.h"

/*
** Applique la fonction f à chaque caractère de la
** chaine de caractères passée en argument pour créer
** une nouvelle chaine de caractères (avec malloc(3))
** résultant des applications successives de f.
** =========
** #1 : la chaine de caractères sur laquelle itérer
** #2 : la fonction à appliquer à chaque caractère
** =========
** Retourne La chaine de caractères résultant des applications
** successives de f, NULL si l’allocationéchoue
*/

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
