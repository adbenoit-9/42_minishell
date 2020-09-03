/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:43:44 by mabriand          #+#    #+#             */
/*   Updated: 2019/11/18 20:41:27 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include "get_next_line.h"
# include "libftprintf.h"

/*
**STRUCTURE
*/

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
**PROTOTYPE
*/

/*
** Char
*/

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
** Convert
*/

char			*ft_itoa(int n);
int				ft_atoi(const char *str);
char			*ft_uitoa(unsigned int n);

/*
** List
*/

t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void	(*del)(void*));


/*
** Memory
*/

void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_calloc(size_t count, size_t size);

/*
** Nbr
*/

size_t			ft_intlen(int n);
size_t			ft_uintlen(unsigned int n);
size_t			ft_hexintlen(unsigned int n);
size_t			ft_long_hexintlen(unsigned long int n);


/*
** Output
*/

void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr(char *s);

/*
** String
*/

char			*ft_strdup(const char *src);
char			*ft_strndup(char *s1, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);

#endif
