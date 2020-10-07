/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:44:11 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/07 11:46:24 by rpet          ########   odam.nl         */
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
#include <signal.h>

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
**	functions which waits for the child process to end
*/

void	wait_process(t_vars *vars, t_exec *exec)
{
	int		status;

	waitpid(exec->pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		vars->signal = WTERMSIG(status);
		vars->ret = vars->signal + 128;
	}
	if (WIFEXITED(status))
		vars->ret = WEXITSTATUS(status);
	if (exec->bin_path)
		free(exec->bin_path);
}

/*
**	function which executes the builtin or internal function
*/

void	exec_command(t_command *command, t_vars *vars, t_exec *exec)
{
	if (!command->args[0])
		return ;
	is_builtin(command, vars);
	if (vars->builtin == BUILTIN)
		return ;
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
	wait_process(vars, exec);
}

/*
**	function to duplicate an open fd and close it
*/

void	duplicate_fd(int tmp_fd[2])
{
	if (dup2(tmp_fd[READ_END], STDIN_FILENO) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (dup2(tmp_fd[WRITE_END], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	close(tmp_fd[READ_END]);
	close(tmp_fd[WRITE_END]);
}

/*
**	main loop for execution of commands
*/

void	iterate_command(t_list *command_list, t_vars *vars)
{
	t_exec	exec;
	int		tmp_fd[2];

	exec.in = STDIN_FILENO;
	signal(SIGINT, signal_exec);
	signal(SIGQUIT, signal_exec);
	exec.fd[WRITE_END] = STDOUT_FILENO;
	while (command_list)
	{
		vars->signal = 0;
		exec.bin_path = NULL;
		tmp_fd[READ_END] = dup(STDIN_FILENO);
		tmp_fd[WRITE_END] = dup(STDOUT_FILENO);
		set_pipes(&exec, command_list);
		if (input_redir(((t_command*)command_list->content)))
			return ;
		if (output_redir(((t_command*)command_list->content)))
			return ;
		exec_command(((t_command*)command_list->content), vars, &exec);
		if (command_list->next)
			exec.in = exec.fd[READ_END];
		duplicate_fd(tmp_fd);
		signal_write_exec(vars);
		command_list = command_list->next;
	}
}
