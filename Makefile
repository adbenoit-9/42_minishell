# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 23:32:24 by adbenoit          #+#    #+#              #
#    Updated: 2020/08/26 00:39:31 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

INC			=	includes/

HEADER		=	$(INC)minishell.h

SRCS_PATH	=	./

SRCS		=	deal_list.c		deal_output.c \
				ft_error.c		ft_strncmp.c \
				main.c			parsing.c \
				ft_strlen.c		init_lst.c

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

OBJ_PATH	=	obj/

OBJS_NAME	=	$(SRCS:.c=.o)

OBJS		=	$(addprefix $(OBJ_PATH),$(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\n"
	@$(CC) -o $(NAME) $(OBJS)
	@echo "Compilation of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]"

$(OBJ_PATH)%.o:	$(SRCS_PATH)%.c $(HEADER)
	@printf "\033[34;1m|\033[0;m"
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[33;1m$(NAME)\033[0;1m: objects deleted\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@echo "\033[33;1m$(NAME)\033[0;1m: $(NAME) deleted\033[0m"

re: fclean all

debug:
	@echo "\033[34;1mOBJS\033[0;m = $(OBJS)"
	@echo "\033[34;1mHEADER\033[0;m = $(HEADER)\n"