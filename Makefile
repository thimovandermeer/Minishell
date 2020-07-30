# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/24 11:54:19 by rpet          #+#    #+#                  #
#    Updated: 2020/07/23 14:58:36 by thimovander   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
SRCSDIR = srcs/
OBJSDIR = objs/
SRCNAMES = $(shell ls $(SRCSDIR) | grep -E ".+\.c")
OBJS = $(addprefix $(OBJSDIR),$(SRCNAMES:.c=.o))
LIBFTDIR = libft/
LIBFT = libft.a
LIBFTDIR = libft/

all: $(NAME)

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p objs
	@gcc $(FLAGS) -I. -c $< -o $@

$(LIBFT):
	cd $(LIBFTDIR) && make && mv $(LIBFT) ..

$(NAME): $(LIBFT) $(OBJS)
	@gcc -L. -lft -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	cd $(LIBFTDIR) && make clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re