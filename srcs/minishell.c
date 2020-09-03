/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/03 09:24:45 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

int 	is_builtin(t_command *command, t_vars *vars)
{
	(void) vars;
	if (!command->args[0])
		command->err = ERROR;
	else if (ft_strcmp(command->args[0], "echo") == 0)
		return (echo_func(command));
	else if (ft_strcmp(command->args[0], "cd") == 0)
		return (cd_func(command, vars->get_env));
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		return (pwd_func());
	// else if (ft_strcmp(command->args[0], "export") == 0)
	// 	vars->ret = (export_func(command));
	// else if (ft_strcmp(command->args[0], "unset") == 0)
	// 	vars->ret = (unset_func(command));
	// else if (ft_strcmp(command->args[0], "env") == 0)
	// 	vars->ret = (env_func(command));
	else if (ft_strcmp(command->args[0], "exit") == 0)
		return (exit_func(command, vars));
	return (0);
}

void		process_list(t_list *list, t_vars *vars, char **env)
{
	t_list		*command_list;

	while (list)
	{
		expand_func(list, vars);
		command_list = parse_line(&list);
		if (!command_list)
			break ;
		iterate_command(command_list, env, vars);
		if (((t_command*)command_list->content)->err == ERROR)
			break ;
		if (!vars->status)
			return ;
	}
}

int			main(int argc, char **argv, char **env)
{
	char		*line;
	t_list		*list;
	t_vars		vars;

	(void) argv;
	if (argc != 1)
	{
		error_general("scripting is not supported");
		return (1);
	}
	init_env(env, &vars);
	vars.status = 1;
	while (vars.status)
	{
		command_prompt();
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_esc);
		if (!get_next_line(0, &line))
			break ;
		list = lexer_line(line);
		if (!check_valid_meta(list))
			continue ;
		print_list(list); //lijst na de lexer
		process_list(list, &vars, env);
		free(line);
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}
