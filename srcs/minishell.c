/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/21 13:44:33 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <unistd.h>

int		is_builtin(t_command *command, t_vars *vars)
{
	if (!command->args[0])
		vars->err = ERROR;
	else if (ft_strcmp(command->args[0], "echo") == 0)
		vars->ret = echo_builtin(command);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		vars->ret = cd_builtin(command, vars->get_env);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		vars->ret = pwd_builtin();
	else if (ft_strcmp(command->args[0], "export") == 0)
		vars->ret = export_builtin(command, vars);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		vars->ret = unset_builtin(vars, command);
	else if (ft_strcmp(command->args[0], "env") == 0)
		vars->ret = env_func(vars);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		vars->ret = exit_builtin(command, vars);
	else
		vars->ret = 1;
	return (vars->ret);
}

void		process_list(t_list *list, t_vars *vars)
{
	t_list		*command_list;

	while (list)
	{
		expand_func(list, vars);
		command_list = parse_line(&list, vars);
		if (!command_list)
			break ;
		iterate_command(command_list, vars);
		if (vars->err == ERROR)
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
		error_general("scripting is not supported", &vars);
		return (1);
	}
	init_env(env, &vars);
	while (vars.status == RUNNING)
	{
		command_prompt();
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_esc);
		if (!get_next_line(0, &line))
			break ;
		list = lexer_line(line, &vars);
		if (!check_valid_meta(list, &vars))
			continue ;
		process_list(list, &vars);
		free(line);
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}
