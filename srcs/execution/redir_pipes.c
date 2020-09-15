#include "minishell.h"
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

void	input_redir(t_command *command)
{
	char	*file;

	command->fd_in = 0;
	while (command->file_in)
	{
		file = (char*)command->file_in->content;
		if (command->fd_in != 0)
			close(command->fd_in);
		open_files(&command->fd_in, file, O_RDONLY, 0644);
		if (command->fd_in == -1)
			return ;
		command->file_in = command->file_in->next;
	}
}

void	output_redir(t_command *command)
{
	int		type;
	char	*file;
	t_list	*tmp_file_out;
	t_list	*tmp_out_mode;

	command->fd_out = 1;
	tmp_file_out = command->file_out;
	tmp_out_mode = command->out_mode;
	while (tmp_file_out)
	{
		file = (char*)command->file_out->content;
		if (command->fd_out != 1)
			close(command->fd_out);
		if (*((t_filemode*)tmp_out_mode->content) == APPEND)
			type = O_APPEND;
		else if (*((t_filemode*)tmp_out_mode->content) == TRUNC)
			type = O_TRUNC;
		open_files(&command->fd_out, file, O_CREAT | type | O_WRONLY, 0644);
		// error handling
		tmp_file_out = tmp_file_out->next;
		tmp_out_mode = tmp_out_mode->next;
	}
}

void	set_pipes(t_exec *exec, t_list *command_list)
{
	if (command_list->next)
		pipe(exec->fd);
	if (exec->in != STDIN_FILENO)
	{
		dup2(exec->in, STDIN_FILENO);
		close(exec->in);
	}
	if (exec->fd[WRITE_END] != STDOUT_FILENO)
	{
		dup2(exec->fd[WRITE_END], STDOUT_FILENO);
		close(exec->fd[WRITE_END]);
	}
}
