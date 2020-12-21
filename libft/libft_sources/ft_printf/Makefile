# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/16 14:05:40 by mabriand          #+#    #+#              #
#    Updated: 2020/01/23 15:36:22 by mabriand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

##################################### PATH #####################################

PTF = ft-printf_sources/
LIBFT = libft/libft_sources/

#################################### SOURCES ####################################

SRCS =	$(PTF)ft_calloc_flag.c			$(PTF)ft_char_add_width.c \
		$(PTF)ft_check_format.c			$(PTF)ft_extract_buffer_part.c \
		$(PTF)ft_format_arg.c			$(PTF)ft_get_format.c \
		$(PTF)ft_get_string.c			$(PTF)ft_hexitoa.c \
		$(PTF)ft_int_add_precision.c	$(PTF)ft_int_add_width.c \
		$(PTF)ft_join.c					$(PTF)ft_print_adress.c \
		$(PTF)ft_print_arguments.c		$(PTF)ft_print_char.c \
		$(PTF)ft_print_nbr.c			$(PTF)ft_print_str.c \
		$(PTF)ft_printf.c				$(PTF)ft_put_formatted_nbr.c \

##################################### BASIC #####################################

CFLAGS = -Wall -Wextra -Werror

CC = gcc

INC = ft-printf_header/

HEADER = $(INC)libftprintf.h

OBJS = $(SRCS:.c=.o)

OBJLIB =	$(LIBFT)get-next-line/*.o	$(LIBFT)libft_char/*.o \
			$(LIBFT)libft_convert/*.o	$(LIBFT)libft_list/*.o \
			$(LIBFT)libft_memory/*.o	$(LIBFT)libft_nbr/*.o \
			$(LIBFT)libft_output/*.o	$(LIBFT)libft_string/*.o \

##################################### RULES #####################################

all: complib $(NAME)

complib:
		$(MAKE) -C libft all

$(OBJS): %.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $@ $(OBJS) $(OBJLIB)
	ranlib $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -f $(PTF)*.o

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re