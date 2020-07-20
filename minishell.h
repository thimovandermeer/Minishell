/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 07:33:20 by rpet          #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/07/20 13:18:09 by rpet          ########   odam.nl         */
=======
/*   Updated: 2020/07/16 13:28:34 by thimovander   ########   odam.nl         */
>>>>>>> 411ade586232a20e9ae6b2e273b492071af55b8a
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
	//int			quote;
	//int			in_token;
	int			token_len;
	char		*token_str;
	t_quote		quote;
	t_token		token;
}				t_lexer;

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
