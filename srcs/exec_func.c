/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:53:08 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/03 09:33:48 by rpet          ########   odam.nl         */
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

char	*get_bin_path(char *tmp, char *token)
{
	char			**path;
	char			*bin_path;
	char			*temp;
	int				i;
	struct stat		f;

	path = ft_split(tmp, ':');
	if (!path)
		error_malloc();
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		bin_path = ft_strjoin(temp, token);
		if (lstat(bin_path, &f) == -1 && bin_path)
			free(bin_path);
		else
		{
			ft_free_array(path);
			return (bin_path);
		}
		i++;
	}
	ft_free_array(path);
	return (NULL);
}

int		check_bins(t_command *cmd, char **env, t_vars *vars, int cmd_num)
{
	char		**tmp;
	char		*bin_path;
	int			i;

	i = 0;
	while (env[i] != '\0')
	{
		tmp = ft_split(env[i], '=');
		if (!tmp)
			error_malloc();
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			bin_path = get_bin_path(tmp[1], cmd->args[0]);
			if (bin_path)
				return (ft_executable(bin_path, cmd, env, vars, cmd_num));
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int		ft_executable(char *bin_path, t_command *command,
									char **env, t_vars *vars, int command_num)
{
	pid_t 		p_id;

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
	else if (p_id == -1)
	{
		error_general(strerror(errno));
		return (0);
	}
	wait(NULL);
	if (command_num != vars->commands - 1)
		close(vars->fd[command_num][1]);
	if (command_num > 0)
		close(vars->fd[command_num -1][0]);
	return (1);
}

void	open_files(t_command *command, t_vars *vars, int command_num)
{
	if (command->redir == REDIR_IN)
		vars->fd[command_num][0] = open(command->file_in, O_RDONLY);
	if (command->redir == REDIR_OUT_NEW)
		vars->fd[command_num][1] = open(command->file_out,
										O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (command->redir == REDIR_OUT_APPEND)
		vars->fd[command_num][1] = open(command->file_out,
										O_CREAT | O_APPEND | O_RDWR, 0644);
}

int 	pipes_counter(t_list *command_list)
{
	int i;

	i = 0;
	while (command_list)
	{
		i++;
		command_list = command_list->next;
	}
	return (i - 1);
}

int		set_pipes(t_list *command_list, t_vars *vars)
{
	int		pipe_amount;
	int		i;

	pipe_amount = pipes_counter(command_list);
	if (pipe_amount == 0)
		return (1);
	vars->fd = (int**)malloc(sizeof(int*) * pipe_amount);
	if (!vars->fd)
		error_malloc();
	i = 0;
	while (i < pipe_amount)
	{
		vars->fd[i] = malloc(sizeof(int) * 2);
		if (!vars->fd[i])
		{
			free_int_array(vars->fd);
			error_malloc();
		}
		pipe(vars->fd[i]);
		i++;
	}
	return (1);
}

void	count_commands(t_list *command_list, t_vars *vars)
{
	vars->commands = 0;
	while (command_list)
	{
		command_list = command_list->next;
		vars->commands++;
	}
}

void	iterate_command(t_list *command_list, char **env, t_vars *vars)
{
	t_command	*command;
	int			i;

	i = 0;
	command = ((t_command*)command_list->content);
	if(!set_pipes(command_list, vars))
		return ;
	if (command->redir != NO_REDIR)
		open_files(command, vars, i);
	count_commands(command_list, vars);
	while (command_list)
	{
		if (!is_builtin(command, vars))
		{
			if (!vars->status)
				return ;
			if (command->err == ERROR)
			{
				if (command->pipe == NO_PIPE)
					error_syntax(";");
				else
					error_syntax("|");
				return ;
			}
			else if (!check_bins(command, env, vars, i))
				error_invalid_cmd(command->args[0]);
		}
		command_list = command_list->next;
		i++;
	}
}
