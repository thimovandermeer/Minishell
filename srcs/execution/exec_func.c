#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void	executable(t_exec *exec, t_command *command, t_vars *vars)
{
	execve(exec->bin_path, command->args, vars->get_env);
	// error handling wanneer path wel gevonden is maar niet uit kan voeren.
	exit(126);
}

void	open_files(int *fd, char *file, int type, mode_t mode)
{
	*fd = open(file, type, mode);
	if (*fd == -1)
		printf("gaat fout bij open files\n");
}

// void	signal_handling(t_exec *exec, )
// {
// 	waitpid()
// }

void	is_internal(t_command *command, t_vars *vars, t_exec *exec)
{
	int ret;

	if (!check_bins(command, vars, exec))
	{
		error_invalid_cmd(command->args[0], vars);
		vars->ret = 127;
		return ;
	}
	exec->pid = fork();
	if (exec->pid == 0)
		executable(exec, command, vars);
	if (exec->pid < 0)
	{
		free(exec->bin_path);
		printf("gaat fout bij exec");		
		return ;
	}
	// signal_handling();
	waitpid(exec->pid, &ret, WUNTRACED);
	if (exec->bin_path)
		free(exec->bin_path);
}

void	exec_func(t_command *command, t_vars *vars, t_exec *exec)
{
	// builtin uitvoeren
	if (is_builtin(command, vars) == 1)
		is_internal(command, vars, exec);
}

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
		// signal handling hier voor quit etc
		command_list = command_list->next;
	}
}
