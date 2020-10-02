/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:44:11 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/02 11:29:18 by thvan-de      ########   odam.nl         */
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
		error_malloc();
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
	if (is_builtin(command, vars) == 1)
		is_internal(command, vars, exec);
}

/*
**	Main loop for execution of commands
*/

void	iterate_command(t_list *command_list, t_vars *vars)
{
	t_exec	exec;
	int		tmp_fd[2];

	exec.in = STDIN_FILENO;
	exec.fd[WRITE_END] = STDOUT_FILENO;
	while (command_list)
	{
		exec.bin_path = NULL;
		tmp_fd[READ_END] = dup(STDIN_FILENO);
		tmp_fd[WRITE_END] = dup(STDOUT_FILENO);
		set_pipes(&exec, command_list);
		if (input_redir(((t_command*)command_list->content)))
			return ;
		if (output_redir(((t_command*)command_list->content)))
			return ;
		exec_func(((t_command*)command_list->content), vars, &exec);
		if (command_list->next)
			exec.in = exec.fd[READ_END];
		dup2(tmp_fd[READ_END], STDIN_FILENO);
		dup2(tmp_fd[WRITE_END], STDOUT_FILENO);
		close(tmp_fd[READ_END]);
		close(tmp_fd[WRITE_END]);
		command_list = command_list->next;
	}
}
