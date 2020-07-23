# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 14:42:36 by rpet          #+#    #+#                  #
#    Updated: 2020/07/21 13:30:25 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
	   ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	   ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_strcmp.c get_next_line.c get_next_line_utils.c \
	   ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	gcc -c $< -o $@ -I. $(FLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
