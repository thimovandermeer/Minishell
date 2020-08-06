/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:53:08 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/06 14:41:19 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char	*get_bin_path(char *tmp, char *token)
{
	char			**path;
	int				i;
	char			*bin_path;
	struct stat		f;

	i = 0;
	path = ft_split(tmp, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		bin_path = ft_strjoin(path[i], token);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
			return (bin_path);
		i++;
	}
	return (NULL);
}

int		check_bins(t_command *command, char **env, t_vars *vars, int command_num)
{
	char			**tmp;
	char			*bin_path;
	int				i;

	i = 0;
	while (env[i] != '\0')
	{
		tmp = ft_split(env[i], '=');
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			bin_path = get_bin_path(tmp[1], command->args[0]);
			if (bin_path != NULL)
				return (ft_executable(bin_path, command, env, vars, command_num));
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

int		ft_executable(char *bin_path, t_command *command,
char **env, t_vars *vars, int command_num)
{
	pid_t p_id;

	p_id = fork();
	if (p_id == 0)
	{
		if (command->pipe == PIPE_BOTH)
		{
			dup2(vars->fd[command_num - 1][0], 0);
			close(vars->fd[command_num - 1][1]);
			dup2(vars->fd[command_num][1], 1);
			close(vars->fd[command_num][0]);
		}
		else if (command->pipe == PIPE_OUT && command->redir == NO_REDIR)
		{
			dup2(vars->fd[command_num][1], 1);
			close(vars->fd[command_num][0]);
		}
		else if (command->pipe == PIPE_IN && command->redir == NO_REDIR)
			dup2(vars->fd[command_num - 1][0], 0);
		else if (command->redir != NO_REDIR)
		{
			if (command->redir == REDIR_IN)
				dup2(vars->fd[command_num][0], 0);
			if (command->redir == REDIR_OUT_APPEND ||
			command->redir == REDIR_OUT_NEW)
				dup2(vars->fd[command_num][1], 1);
		}
		execve(bin_path, command->args, env);
		exit(1);
	}
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(NULL);
	if (command_num != vars->commands - 1)
		close(vars->fd[command_num][1]);
	if (command_num > 0)
		close (vars->fd[command_num -1][0]);
	return (0);
}

void	open_files(t_command *command, t_vars *vars, int command_num)
{
	if (command->redir == REDIR_IN)
		vars->fd[command_num][0] = open(command->file_in, O_RDONLY);
	if (command->redir == REDIR_OUT_NEW)
		vars->fd[command_num][1] = open(command->file_out, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (command->redir == REDIR_OUT_APPEND)
		vars->fd[command_num][1] = open(command->file_out, O_CREAT |
		O_APPEND | O_RDWR, 0644);
}

int 	pipes_counter(t_list *command_list)
{
	int i;

	i = 0;
	while (command_list != NULL)
	{
		i++;
		command_list = command_list->next;
	}
	return (i - 1);
}

void		set_pipes(t_list *command_list, t_vars *vars)
{
	int		pipes;
	int		i;

	pipes = pipes_counter(command_list);
	if (pipes == 0)
		return ;
	vars->fd = (int**)malloc(sizeof(int*) * pipes);
	i = 0;
	while (i < pipes)
	{
		vars->fd[i] = malloc(sizeof(int) * 2);
		pipe(vars->fd[i]);
		i++;
	}
}

void	count_commands(t_list *command_list, t_vars *vars)
{
	vars->commands = 0;
	while (command_list != NULL)
	{
		command_list = command_list->next;
		vars->commands++;
	}
}

void	iterate_command(t_list *command_list, char **env, t_vars *vars)
{
	int i;

	i = 0;
	set_pipes(command_list, vars);
	if (((t_command*)command_list->content)->redir != NO_REDIR)
		open_files(((t_command*)command_list->content), vars, i);
	count_commands(command_list, vars);
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content), vars, i) == 0 &&
		check_bins(((t_command*)command_list->content), env, vars, i) == -1)
			vars->ret = 127;
		command_list = command_list->next;
		i++;
	}
}
