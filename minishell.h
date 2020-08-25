/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:35:32 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/25 18:27:37 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define ECHO 0
#define ECHO_N 7
#define CD 1
#define PWD 2
#define ENV 3
#define EXPORT 4
#define UNSET 5
#define EXIT 6
#define UNKOWN 8
#define ERROR 9

#define PIPE 0
#define COMA 1
#define RIGHT 2
#define LEFT 3
#define D_RIGHT 4
#define D_LEFT 5
#define AND 6
#define OR 7

#include <unistd.h>
#include <stdlib.h>

typedef struct	s_order
{
	char			*output;
	char			*input;
	int				command;
	int				sep;
	int				ret;
	struct s_order	*next;
}				t_order;

void 	set_output(char *input, char **output);
size_t	ft_strlen(const char *s);

#endif
