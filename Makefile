NAME = minishell
FLAGS = -Wall -Werror -Wextra
SDIR = srcs
ODIR = objs
_OBJS = minishell \
		builtins/cd_builtin \
		builtins/echo_builtin \
		builtins/env_builtin \
		builtins/exit_builtin \
		builtins/export_builtin \
		builtins/pwd_builtin \
		builtins/unset_builtin \
		execution/exec_func \
		execution/get_path \
		execution/redir_pipes\
		lexer/check_valid_input \
		lexer/lexer \
		lexer/lexer_esc_char \
		lexer/lexer_status \
		parser/create_func \
		parser/expand_func \
		parser/init_env_func \
		parser/parse_func \
		parser/remove_quotes \
		parser/remove_quotes_status \
		parser/shell_expansion_status \
		parser/shell_replace \
		utils/command_prompt \
		utils/error \
		utils/error_exec \
		utils/free_functions \
		utils/parse_utils \
		utils/signals \
		utils/utils
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
