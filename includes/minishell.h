/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 14:08:14 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/07 11:44:16 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stddef.h>

# define READ_END 0
# define WRITE_END 1

typedef enum	e_status {
	STOP,
	RUNNING,
}				t_status;

typedef enum	e_error {
	NO_ERROR,
	ERROR
}				t_error;

typedef enum	e_escape {
	NO_ESCAPE,
	ESCAPE
}				t_escape;

typedef enum	e_token {
	NOT_ACTIVE,
	ACTIVE,
	METACHAR,
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

typedef	enum	e_filemode
{
	APPEND,
	TRUNC
}				t_filemode;

typedef enum	e_pipe
{
	NO_PIPE,
	PIPE_IN,
	PIPE_OUT,
	PIPE_BOTH
}				t_pipe;

typedef enum	e_builtin
{
	NO_BUILTIN,
	BUILTIN
}				t_builtin;

typedef	struct	s_lexer {
	int				token_len;
	char			*token_str;
	char			*tmp;
	char			metachar;
	t_escape		escape;
	t_quote			quote;
	t_token			token;
}				t_lexer;

typedef struct	s_parsing {
	t_list			*list;
	t_separator		cur_sep;
	t_separator		prev_sep;
	t_error			err;
}				t_parsing;

typedef struct	s_command {
	char			**args;
	t_pipe			pipe;
	t_list			*file_in;
	t_list			*file_out;
	t_list			*out_mode;
	int				fd_out;
	int				fd_in;
}				t_command;

typedef struct	s_vars {
	char		**env;
	char		*token;
	int			commands;
	int			ret;
	int			signal;
	t_builtin	builtin;
	t_status	status;
	t_quote		quote;
	t_escape	escape;
}				t_vars;

typedef	struct	s_exec {
	pid_t			pid;
	char			*bin_path;
	int				fd[2];
	int				in;
}				t_exec;

/*
**		Cd functions
*/

void			set_pwd(t_vars *vars, int var_index, char *env_var, char *loc);
void			update_pwd(t_vars *vars, char *new_pwd);
int				cd_old(t_vars *vars);
int				cd_home(t_vars *vars);
int				cd_builtin(t_command *command, t_vars *vars);

/*
**		Echo functions
*/
int				echo_builtin(t_command *command, t_vars *vars);

/*
**		Env functions
*/
int				env_func(t_vars *vars);

/*
**		Exit functions
*/

int				str_is_num(char *str);
int				exit_invalid_arguments(t_command *command);
int				exit_multiple_arguments(t_command *command, t_vars *vars);
int				exit_builtin(t_command *command, t_vars *vars);

/*
**		export builtin functions
*/

int				check_var_name(char *key);
void			set_env_name(t_vars *vars, char *argument, char **new_var);
void			set_quotes(char *export_print);
void			declare_list_thing(t_command *command, t_vars *vars);
int				export_builtin(t_command *command, t_vars *vars);

/*
**		pwd builtin functions
*/
int				pwd_builtin(t_vars *vars);

/*
**		unset builtin functions
*/

int				find_var_in_env(char *search_var, char **tmp_env);
void			recreate_env_list(t_vars *vars, int index, int skip_loc);
int				unset_builtin(t_vars *vars, t_command *command);

/*
**		execution exec func
*/

void			open_files(int *fd, char *file, int type, mode_t mode);
void			wait_process(t_vars *vars, t_exec *exec);
void			exec_command(t_command *command, t_vars *vars, t_exec *exec);
void			duplicate_fd(int tmp_fd[2]);
void			iterate_command(t_list *command_list, t_vars *vars);

/*
**		execution get path
*/

char			*create_new_binpath(char **path, char *token, int i);
char			*get_bin_path(char *tmp, char *token);
int				check_bins(t_command *command, t_vars *vars, t_exec *exec);

/*
**		execution redir pipes
*/

int				input_redir(t_command *command);
int				type_determination(t_command *command, t_list *tmp_out_mode);
int				output_redir(t_command *command);
void			set_pipes(t_exec *exec, t_list *command_list);

/*
**		Lexer functions check_valid_input
*/

int				is_redirection(char *token);
int				syntax_redirections(t_list *list, t_vars *vars);
int				syntax_seperators(t_list *list, t_vars *vars);
int				check_valid_input(t_list *list, t_vars *vars);

/*
**		Lexer functions lexer
*/

int				is_metachar(char cur_char);
void			add_token_to_list(t_lexer *lexer, t_list **list);
void			lexer_loop(char *line, t_lexer *lexer, t_list **list);
void			init_lexer(t_lexer *lexer);
t_list			*lexer_line(char *line);

/*
**		Lexer functions lexer esc char
*/

void			found_escape_char(char *line, t_lexer *lexer);

/*
**		Lexer functions lexer status
*/

void			found_double_quote(char *line, t_lexer *lexer);
void			found_single_quote(char *line, t_lexer *lexer);
void			outside_token(char *line, t_lexer *lexer);
void			in_active_token(char *line, t_lexer *lexer, t_list **list);
void			in_metachar_token(char *line, t_lexer *lexer, t_list **list);

/*
**		parser functions create func
*/

t_list			*make_item(int arg_count, t_vars *vars);
void			create_command(t_parsing *parser, t_list **command_list,
								t_vars *vars);
void			add_list(t_list **list, void *content);

/*
**		parser functions expand func
*/

void			expand_loop(t_list *list, t_vars *vars);
void			shell_expansion(t_vars *vars, char *old);

/*
**		parser functions init env func
*/

size_t			ft_env_len(char **env);
void			init_env(char **env, t_vars *vars);
char			*search_var_name(char *search_val, char **search_place);
t_quote			check_quote_type(t_list *list);

/*
**		parser functions parse func
*/

void			redir_handling(t_parsing *parser, t_command *command,
								t_redirection redir);
void			parse_pipes(t_command *command, t_parsing *parser);
void			parse_command(t_command *command, t_parsing *parser,
								t_vars *vars);
void			no_sep_found_parsing(t_parsing *parsing, t_list **command_list,
									t_list **list, t_vars *vars);
t_list			*parse_line(t_list **list, t_vars *vars);

/*
**		parser functions remove quotes status
*/

void			double_quote(t_vars *vars, int *i, char c);
void			single_quote(t_vars *vars, int *i, char c);
void			escape(t_vars *vars, int *i, char c, char special);

/*
**		parser functions remove quotes status
*/

void			resize_token(t_vars *vars, int len);
void			quote_loop(char *old, t_vars *vars);
void			remove_quotes(char *old, t_vars *vars);

/*
**		Util functions command prompt
*/

void			command_handler(int sig_num);
void			fork_handler(int sig_num);
void			command_prompt(void);

/*
**		Util functions error functions
*/

void			error_general(char *error_msg, t_vars *vars);
void			error_malloc(void);
void			error_invalid_cmd(char *arg, t_vars *vars);
void			error_syntax(char *arg, t_vars *vars);
void			error_identifier(char **arg, t_vars *vars);

/*
**		Util functions free functions
*/

void			free_command_table(t_list **command_list);
void			free_array(char **arr);
void			free_content(void *content);

/*
**		Util functions parse utils
*/

t_separator		check_seperator(char *str);
t_redirection	check_redir(char *str);
int				get_length(t_parsing *parser);
void			free_pipe_parse_line(t_list **tmp);
void			free_parse_line(t_list **list);

/*
**		Util functions signals
*/

void			signal_handler(int sig_num);
void			signal_exec(int sig_num);
void			signal_write_exec(t_vars *vars);

/*
**		parse functions expansion status
*/

int				shell_sign(t_vars *vars, int i);
void			shell_double_quote(t_vars *vars);
void			shell_single_quote(t_vars *vars);
void			shell_escape(t_vars *vars);

/*
**		Util functions utils
*/

char			*get_env(char **env, char *key);
char			**set_new_env(char **array, int length);
char			**bubblesort(char **array, int length);

int				replace_env(t_vars *vars, char *replace, int i);
int				env_len(char *env);
char			*find_env(t_vars *vars, int i);

/*
**		Util functions error exec
*/

void			error_str_error(char *arg, char *str_error);

/*
**		Minishell
*/

int				is_builtin(t_command *command, t_vars *vars);
void			process_list(t_list *list, t_vars *vars);
void			minishell_loop(t_vars *vars);

#endif
