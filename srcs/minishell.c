/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/03 11:46:06 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	is_builtin(t_command *command)
{
	if (ft_strncmp(command->args[0], "echo", ft_strlen("echo")) == 0)
		return (echo_func(command->args[1])); // all deze funcites 1 laten returen als het goed gaat
	if(ft_strncmp(command->args[0], "ECHO", ft_strlen("echo")) == 0)
		return (echo_func(command->args[1]));
	if(ft_strncmp(command->args[0], "cd", ft_strlen("cd")) == 0)
		return (cd_func(command->args[1]));
	if(ft_strncmp(command->args[0], "pwd", ft_strlen("pwd")) == 0)
		return (pwd_func(command->args[1]));
	if(ft_strncmp(command->args[0], "export", ft_strlen("export")) == 0)
		return (export_func(command->args[1]));
	if(ft_strncmp(command->args[0], "unset", ft_strlen("unset")) == 0)
		return (unset_func(command->args[1]));
	if(ft_strncmp(command->args[0], "env", ft_strlen("env")) == 0)
		return (env_func(command->args[1]));
	if(ft_strncmp(command->args[0], "exit", ft_strlen("exit")) == 0)
		return (exit_func(command->args[1]));
	return (0);
}

int			main(int argc, char **argv, char **env)
{
	int     	i;
	char    	*line;
	t_list		*list;
	t_list 		*command_list;
	// t_vars		vars;
	(void)argv;
	(void)argc;
	i = 1;
	// init_envv(env, &vars);
    while (i)
    {
		command_prompt();
		i = get_next_line(0, &line);
		if (i == -1)
			ft_error("Something went wrong reading the line\n");
		list = lexer_line(line);
		print_list(list);
		if (list == NULL)
			str_error("Something went wrong during the lexer\n");
		command_list = parse_line(list);
		iterate_command(command_list, env);
	}
	return (0);
}
