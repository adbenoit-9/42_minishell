/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:00:53 by mabriand          #+#    #+#             */
/*   Updated: 2020/01/23 11:44:59 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <stdarg.h>
# include "libft.h"

/*
**STRUCTURE
*/

typedef struct	s_format
{
	int		flag;
	int		width;
	int		precision;
	int		dot;
	char	specifier;
}				t_format;

typedef struct	s_position
{
	size_t	index;
	size_t	pos;
}				t_position;

/*
**PROTOTYPE
*/

int				ft_printf(const char	*s, ...);
void			ft_arg(const char	*s, t_position *p_pos, va_list ap, int *pf);

/*
**Basic
*/

char			*ft_join(char	*s1, char	*s2);
char			*ft_str_null(char	*s1, char	*s2);
int				ft_get_string(const char *str, size_t	*p_pos);
int				ft_print_arguments(t_format form, va_list ap);

/*
**Format
*/

t_format		ft_f(const char	*s, size_t	*p_pos, t_format form);
t_format		ft_w(const char	*s, size_t	*p_pos, va_list ap, t_format form);
t_format		ft_p(const char	*s, size_t	*p_pos, va_list ap, t_format form);
char			ft_s(const char	*s, size_t	*p_pos);
t_format		ft_get_format(const char	*s, size_t	*p_pos, va_list ap);
int				ft_check_format(t_format form);
char			*ft_calloc_flag(size_t count, int c);

/*
**String
*/

int				ft_print_str(t_format format, va_list ap);
char			*ft_extract_buffer_part(int precision, char	*buffer);
int				ft_format_trans(int	*ptr_precision, int	*p_width, char	*s);
char			*ft_to_add(int flag, int nbr_space);
char			*ft_printed(int flag, char	*new_buffer, char	*to_add);

/*
**Character
*/

int				ft_print_c(t_format form, va_list ap);
int				ft_print_per(t_format form);
char			*ft_add_front_to_char(char c, char	*s);
char			*ft_add_back_to_char(char c, char	*s);
int				ft_put_formatted_char(t_format form, char c);
void			ft_char_cp(char c, int	*p_with_form);

/*
**Number
*/

char			*ft_hexitoa(unsigned int n, char c);
char			*ft_long_hexitoa(unsigned long n, char c);
char			*ft_int_add_precision(char	*nbr, int precision);
char			*ft_int_add_width(t_format form, char *nbr);
int				ft_put_formatted_nbr(t_format form, char	*number);
int				ft_print_signed_dec(t_format form, va_list ap);
int				ft_print_unsigned_dec(t_format form, va_list ap);
int				ft_print_hex(t_format form, va_list ap);
int				ft_print_adr(t_format	form, va_list ap);
char			*ft_zeroes_cp(int cp, int size);
char			*ft_int_cp(int precision, int width, int len, char	*nbr);
int				ft_print_adr_cp(void *adr, t_format format);

#endif
