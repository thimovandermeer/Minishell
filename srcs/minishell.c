/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:47:14 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/07 10:58:30 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

int		is_builtin(t_command *command, t_vars *vars)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		vars->ret = echo_builtin(command, vars);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		vars->ret = cd_builtin(command, vars);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		vars->ret = pwd_builtin(vars);
	else if (ft_strcmp(command->args[0], "export") == 0)
		vars->ret = export_builtin(command, vars);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		vars->ret = unset_builtin(vars, command);
	else if (ft_strcmp(command->args[0], "env") == 0)
		vars->ret = env_func(vars);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		vars->ret = exit_builtin(command, vars);
	else
	{
		vars->ret = 1;
		vars->builtin = NO_BUILTIN;
	}
	return (vars->ret);
}

void	process_list(t_list *list, t_vars *vars)
{
	t_list		*command_list;

	while (list)
	{
		expand_loop(list, vars);
		command_list = parse_line(&list, vars);
		if (!command_list)
			break ;
		iterate_command(command_list, vars);
		if (!vars->status)
			return ;
		free_command_table(&command_list);
	}
}

void	minishell_loop(t_vars *vars)
{
	t_list		*list;
	char		*line;

	while (vars->status == RUNNING)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		command_prompt();
		if (!get_next_line(0, &line))
			break ;
		list = lexer_line(line);
		if (check_valid_input(list, vars))
			process_list(list, vars);
		else
			ft_lstclear(&list, free_content);
		free(line);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_vars		vars;

	(void)argv;
	if (argc != 1)
	{
		error_general("scripting is not supported", &vars);
		return (1);
	}
	init_env(env, &vars);
	minishell_loop(&vars);
	free_array(vars.env);
	ft_putstr_fd("exit\n", 1);
	return (vars.ret);
}
