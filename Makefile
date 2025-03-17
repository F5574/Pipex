# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 16:40:24 by gvon-ah-          #+#    #+#              #
#    Updated: 2025/03/17 17:15:46 by gvon-ah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = #add .c files here

NAME = pipex

LIBFT = $(LIBFT)/libft.a

LIBFT_DIR = ./inc/libft

COMPRESS = ar rcs

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

CC = cc

MAIN = main.c

SRCS_DIR = srcs/

OBJS_DIR = objs/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

$(OBJS_DIR)/%.0: %.c
	@mkdir -p $(OBJS_DIR)
	@$(cc) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) Compiled!

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo Clean all objs!

fclean: clean
	@$(RM) $(NAME) pipex
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo Clean all!

re: fclean all

.PHONY: all fclean clean