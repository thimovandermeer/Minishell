/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 07:33:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/07/28 14:13:37 by thimovander   ########   odam.nl         */
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

typedef enum	e_separator
{
	NO_SEP,
	SEMICOLON,
	PIPE
}				t_separator;

typedef	struct	s_lexer {
	int			token_len;
	char		*token_str;
	t_quote		quote;
	t_token		token;
}				t_lexer;

typedef enum 	e_pipe
{
	NO_PIPE,
	PIPE_IN,
	PIPE_OUT,
	PIPE_BOTH
}				t_pipe;

typedef struct s_parsing {
	t_list 			*list;
	t_separator 	cur_sep;
	t_separator 	prev_sep;
}				t_parsing;

typedef struct s_command {
	char	**args;
	t_pipe	pipe;
	int		fd[2]; 	
}				t_command;

// typedef struct	s_vars {
// 	char		**get_envv;
// 	char		*bin_path;
// 	struct stat f;
// }				t_vars;

/*
**		Lexer functions
*/

void	found_double_quote(char *line, t_lexer *lexer);
void	found_single_quote(char *line, t_lexer *lexer);
int		check_metachar(char *line);
int		add_token_to_list(t_lexer *lexer, t_list **list);
void	check_new_token1(char *line, t_lexer *lexer);
int		check_new_token2(char *line, t_lexer *lexer, t_list **list);
int		lexer_loop(char *line, t_lexer *lexer, t_list **list);
void	init_lexer(t_lexer *lexer);
t_list	*lexer_line(char *line);

/*
**		exec functions
*/

int  	check_bins(t_command *command, char **env);
int 	ft_executable(char *bin_path, t_command *command, char **env);
void 	iterate_command(t_list *command_list, char **env);

/*
**		util functions
*/

void	ft_error(char *str);
int 	ft_occurence(char *line, char c);
void 	ft_free_array(char **arr);
void    print_list(t_list *list);
void    str_error(char *str);
void    print_commands(t_list *command_list);

/*
**		parse functions
*/

t_separator		check_seperator(char *str);
t_list 	*parse_line(t_list *list);


/*
**		init env  functions
*/

size_t 	ft_env_len(char **envv);
// void	init_envv(char **envv, t_vars *vars);

/*
**		pipe handling functions
*/
void 	pipe_handling(t_command *command, char *bin_path, char **env, pid_t p_id);

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
int 	is_builtin(t_command *command);

#endif
