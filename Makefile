# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/24 11:54:19 by rpet          #+#    #+#                  #
#    Updated: 2020/10/01 14:12:42 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
SDIR = srcs
ODIR = objs
_OBJS = minishell \
builtins/cd_builtin builtins/echo_builtin builtins/env_builtin\
builtins/exit_builtin builtins/export_builtin builtins/pwd_builtin \
builtins/unset_builtin execution/exec_func execution/get_path execution/redir_pipes\
lexer/check_valid_input lexer/lexer lexer/lexer_status lexer/lexer_esc_char \
parser/expand_func parser/init_env_func parser/parse_func parser/remove_quotes \
parser/remove_quotes_status parser/shell_expansion_status \
utils/command_prompt utils/error utils/parse_utils utils/signals \
utils/utils utils/free_functions parser/create_func

OBJS =	$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
LIBFT = libft.a
LIBFTMAP = libft
INC = includes
CC = gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTMAP)/$(LIBFT)
	gcc $(OBJS) -L$(LIBFTMAP) -lft -o $(NAME)

$(LIBFTMAP)/$(LIBFT):
	make -C $(LIBFTMAP)

test: all
	./minishell

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	@mkdir -p $(ODIR)/$(dir $*)
	gcc $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFT)
	make clean -C $(LIBFTMAP)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTMAP)

re: fclean all
