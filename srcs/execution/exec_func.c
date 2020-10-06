/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:44:11 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/06 11:40:13 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

/*
**	function which opens files with the given file type and mode
*/

void	open_files(int *fd, char *file, int type, mode_t mode)
{
	*fd = open(file, type, mode);
	if (*fd == -1)
		error_str_error(file, strerror(errno));
}

/*
**	function which executes the internal functions
*/

void	is_internal(t_command *command, t_vars *vars, t_exec *exec)
{
	int		status;

	if (!check_bins(command, vars, exec))
	{
		error_invalid_cmd(command->args[0], vars);
		return ;
	}
	exec->pid = fork();
	if (exec->pid == 0)
	{
		execve(exec->bin_path, command->args, vars->env);
		error_str_error(command->args[0], strerror(errno));
		exit(126);
	}
	if (exec->pid < 0)
	{
		free(exec->bin_path);
		error_general("something went wrong during fork proces", vars);
		return ;
	}
	waitpid(exec->pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		vars->ret = WEXITSTATUS(status);
	if (exec->bin_path)
		free(exec->bin_path);
}

/*
**	function which decides if the function is a internal of builtin function
*/

void	exec_func(t_command *command, t_vars *vars, t_exec *exec)
{
	if (is_builtin(command, vars) == 1 && vars->builtin == NO_BUILTIN)
		is_internal(command, vars, exec);
}

/*
**	function which decides if the function is a internal of builtin function
*/

void	close_pipes(t_vars *vars, int n)
{
	printf(" n = [%i]\n", n);
	if (vars->pipes)
	{
		printf("first if\n");
		if (vars->pipes[n] && vars->pipes[n][1] > 1)
		{
			close(vars->pipes[n][1]);
			vars->pipes[n][1] = -1;
		}
		printf("second if\n");
		if (n > 0 && vars->pipes[n - 1] && vars->pipes[n - 1][0] > 1)
		{
			close(vars->pipes[n - 1][0]);
			vars->pipes[n - 1][0] = -1;
		}
	}
}

/*
**	Main loop for execution of commands
*/

void	iterate_command(t_list *command_list, t_vars *vars)
{
	t_exec	exec;
	int		n;
	int		i;

	n = 0;
	i = 0;

	// hier moet gesplit worden op ;
	n = 0;
	// hier moeten we lopen of de commands
	printf("cmd amount = %i\n", vars->cmd_amount);
	while (i < vars->cmd_amount)
	{
		n = 0;
		printf("pipes_counter[i] = %i\n", vars->pipes_counter[i]);
		while (n <= vars->pipes_counter[i])
		{
			printf("n = %i\n", n);
			exec.bin_path = NULL;
			if (vars->pipes_counter[i] != 0)
			{
				printf("kom ik hier?\n");
				set_pipes(&exec, command_list, vars);
				redir_locking(vars, n);
			}
			if (input_redir(((t_command*)command_list->content)))
				return ;
			if (output_redir(((t_command*)command_list->content)))
				return ;
			exec_func(((t_command*)command_list->content), vars, &exec);
			printf("voor close pipes\n");
			close_pipes(vars, n);
			printf("na close pipes\n");
			command_list = command_list->next;
			n++;
		}
		i++;
	}
}
