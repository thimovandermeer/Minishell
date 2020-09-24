#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stddef.h>
# include <stdio.h> //norm

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

typedef	struct	s_lexer {
	int			token_len;
	char		*token_str;
	t_quote		quote;
	t_token		token;
}				t_lexer;

typedef enum	e_pipe
{
	NO_PIPE,
	PIPE_IN,
	PIPE_OUT,
	PIPE_BOTH
}				t_pipe;

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
	char		**get_env;
	int			commands;
	int			ret;
	t_status	status;
}				t_vars;

typedef	struct s_exec
{
	pid_t		pid;
	char		*bin_path;
	// char		**args;
	int			fd[2];
	int 		in;
}				t_exec;


/*
**		Lexer functions
*/

void			found_double_quote(char *line, t_lexer *lexer);
void			found_single_quote(char *line, t_lexer *lexer);
void			outside_token(char *line, t_lexer *lexer);
void			in_active_token(char *line, t_lexer *lexer, t_list **list);
void			in_metachar_token(char *line, t_lexer *lexer, t_list **list);
int				check_metachar(char *line);
void			add_token_to_list(t_lexer *lexer, t_list **list);
void			lexer_loop(char *line, t_lexer *lexer, t_list **list);
void			init_lexer(t_lexer *lexer);
t_list			*lexer_line(char *line);
int				is_redirection(char *token);
int				syntax_redirections(t_list *list, t_vars *vars);
int				syntax_seperators(t_list *list, t_vars *vars);
int				check_valid_input(t_list *list, t_vars *vars);

/*
**		get_path.c functions
*/
char			*get_bin_path(char *tmp, char *token);
int				check_bins(t_command *command, t_vars *vars, t_exec *exec);

/*
**		redir_pipes.c functions
*/

int				input_redir(t_command *command);
int				output_redir(t_command *command);
void			set_pipes(t_exec *exec, t_list *command_list);

/*
**		Exec functions
*/

void			executable(t_exec *exec, t_command *command, t_vars *vars);
void			open_files(int *fd, char *file, int type, mode_t mode);
void			is_internal(t_command *command, t_vars *vars, t_exec *exec);
void			exec_func(t_command *command, t_vars *vars, t_exec *exec);
void			iterate_command(t_list *command_list, t_vars *vars);

/*
**		Util functions
*/

int				ft_occurence(char *line, char c);
void			print_list(t_list *list);
void			print_commands(t_list *command_list);
char			*get_env(char **env, char *key);

/*
**		Parse functions
*/

t_separator		check_seperator(char *str);
t_list			*parse_line(t_list **list, t_vars *vars);
t_redirection	check_redir(char *str);

/*
**		Init env functions
*/

size_t			ft_env_len(char **env);
void			init_env(char **env, t_vars *vars);

/*
**		Signal functions
*/

void			ctrl_c(int signal);
void			ctrl_esc(int signal);

/*
**		Pipe handling functions
*/

void			pipe_handling(t_command *command, char *bin_path,
								char **env, pid_t p_id);

/*
**		Expand_func.c
*/

char			*search_var_name(char *search_val, char **search_place);
char			*create_new_token(char *str1, char *str2, int len);
char			*expand_var(char *replace, t_vars *vars, t_quote quote);
void			expand_func(t_list *list, t_vars *vars);
int				get_length_var_name(char *replace);
int				echo_builtin(t_command *command);
int				pwd_builtin(void);
int				export_builtin(t_command *command, t_vars *vars);
int				unset_builtin(t_vars *vars, t_command *command);
int				env_func(t_vars *vars);
void			command_prompt(void);
void			command_handler(int sig_num);
void			fork_handler(int sig_num);
int				is_builtin(t_command *command, t_vars *vars);

/*
**		Cd functions
*/

void			set_pwd(t_vars *vars, int var_index, char *env_var, char *loc);
void			update_pwd(t_vars *vars, char *new_pwd);
int				cd_old(t_vars *vars);
int				cd_home(t_vars *vars);
int				cd_builtin(t_command *command, t_vars *vars);

/*
**		Exit functions
*/

int				str_is_num(char *str);
int				exit_builtin(t_command *command, t_vars *vars);

/*
**		Error functions
*/

void			error_general(char *error_msg, t_vars *vars);
void			error_malloc(void);
void			error_invalid_cmd(char *arg, t_vars *vars);
void			error_syntax(char *arg, t_vars *vars);
char			**bubblesort(char **array, int length);
int				find_var_in_env(char *search_var, char **tmp_env);

/*
**		Free functions
*/

void			free_command_table(t_list **command_list);
void 			free_array(char **arr);
void			free_content(void *content);
#endif
