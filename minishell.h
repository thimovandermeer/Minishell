/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 07:33:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/07/23 13:23:23 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

typedef enum	e_token {
	NOT_ACTIVE,
	ACTIVE,
	METACHAR
}				t_token;

typedef enum	e_quote {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}				t_quote;

typedef	struct	s_lexer {
	int			token_len;
	char		*token_str;
	t_quote		quote;
	t_token		token;
}				t_lexer;

typedef struct s_command {
	char 	**args;
	int 	pipe;
}				t_command;

/*
**		Lexer functions
*/

void	found_double_quote(char *line, t_lexer *lexer);
void	found_single_quote(char *line, t_lexer *lexer);
int		check_metachar(char *line);
int		add_token_to_list(t_lexer *lexer, t_list **list);
void	outside_token(char *line, t_lexer *lexer);
int		in_active_token(char *line, t_lexer *lexer, t_list **list);
int		in_metachar_token(char *line, t_lexer *lexer, t_list **list);
int		lexer_loop(char *line, t_lexer *lexer, t_list **list);
void	init_lexer(t_lexer *lexer);
t_list	*lexer_line(char *line);

int 	cd_func(char *token);
int 	echo_func(char *token);
int 	env_func(char *token);
int 	exit_func(char *token);
int 	export_func(char *token);
int 	pwd_func(char *token);
int 	unset_func(char *token);
void 	command_prompt();
void    command_handler(int sig_num);
void    fork_handler(int sig_num);

char 	**get_envv;
char 	**tokens;
char	**command;

#endif
