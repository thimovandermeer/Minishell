/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/03 16:38:00 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	is_builtin(t_command *command)
{
	if (ft_strncmp(command->args[0], "echo", ft_strlen("echo")) == 0)
		command->ret = (echo_func(command)); // all deze funcites 0 laten returen als het goed gaat
	// if (ft_strncmp(command->args[0], "ECHO", ft_strlen("echo")) == 0)
	// 	command->ret = (echo_func(command));
	// if (ft_strncmp(command->args[0], "cd", ft_strlen("cd")) == 0)
	// 	command->ret = (cd_func(command));
	// if (ft_strncmp(command->args[0], "pwd", ft_strlen("pwd")) == 0)
	// 	command->ret = (pwd_func(command));
	// if (ft_strncmp(command->args[0], "export", ft_strlen("export")) == 0)
	// 	command->ret = (export_func(command));
	// if (ft_strncmp(command->args[0], "unset", ft_strlen("unset")) == 0)
	// 	command->ret = (unset_func(command));
	// if (ft_strncmp(command->args[0], "env", ft_strlen("env")) == 0)
	// 	command->ret = (env_func(command));
	// if (ft_strncmp(command->args[0], "exit", ft_strlen("exit")) == 0)
	// 	command->ret = (exit_func(command));
	return (0);
}

void		kill_control_c()
{
	
}

void 		kill_control_slash()
{
	
}

int			main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_list		*list;
	t_list		*command_list;

	(void)argv;
	(void)argc;
	i = 1;
	// init_envv(env, &vars);
	while (i)
	{
		command_prompt();
		signal(SIGINT, kill_control_c);
		signal(SIGINT, kill_control_slash);
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
