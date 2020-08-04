/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 07:33:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/08/04 14:18:26 by thvan-de      ########   odam.nl         */
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

typedef enum	e_redirection
{
	NO_REDIR,
	REDIR_IN,
	REDIR_OUT_APPEND,
	REDIR_OUT_NEW
}				t_redirection;

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
	t_redirection 	redir;
}				t_parsing;

typedef struct	s_command {
	char			**args;
	t_pipe			pipe;
	t_redirection 	redir;
	char			*file_in;
	char			*file_out;
	int				ret;
}				t_command;

typedef struct	s_vars {
	int		fd[2];
	char 	**get_envv;
}				t_vars;

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

/*
**		exec functions
*/

int  	check_bins(t_command *command, char **env, t_vars *vars);
int 	ft_executable(char *bin_path, t_command *command, char **env, t_vars *vars);
void 	iterate_command(t_list *command_list, char **env, t_vars *vars);

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
t_list 					*parse_line(t_list *list);
t_redirection			check_redir(char *str);

/*
**		init env  functions
*/

size_t 	ft_env_len(char **envv);
void	init_envv(char **envv, t_vars *vars);

/*
**		pipe handling functions
*/
void 	pipe_handling(t_command *command, char *bin_path, char **env, pid_t p_id);

int 	cd_func(t_command *command);
int 	echo_func(t_command *command);
int 	env_func(t_command *command);
int 	exit_func(t_command *command);
int 	export_func(t_command *command);
int 	pwd_func(t_command *command);
int 	unset_func(t_command *command);
void 	command_prompt();
void    command_handler(int sig_num);
void    fork_handler(int sig_num);
int 	is_builtin(t_command *command);

#endif
