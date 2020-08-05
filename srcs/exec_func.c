/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:53:08 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/05 14:05:10 by thvan-de      ########   odam.nl         */
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

int		check_bins(t_command *command, char **env, t_vars *vars)
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
				return (ft_executable(bin_path, command, env, vars));
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

int		ft_executable(char *bin_path, t_command *command,
char **env, t_vars *vars)
{
	pid_t p_id;

	p_id = fork();
	if (p_id == 0)
	{
		if (command->pipe == PIPE_OUT)
		{
			dup2(vars->fd[1], 1);
			close(vars->fd[0]);
		}
		else if (command->pipe == PIPE_IN)
			dup2(vars->fd[0], 0);
		else if (command->redir != NO_REDIR)
		{
			if (command->redir == REDIR_IN)
				dup2(vars->fd[0], 0);
			if (command->redir == REDIR_OUT_APPEND ||
			command->redir == REDIR_OUT_NEW)
				dup2(vars->fd[1], 1);
		}
		return (execve(bin_path, command->args, env));
	}
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(NULL);
	close(vars->fd[1]);
	return (0);
}

void	open_files(t_command *command, t_vars *vars)
{
	if (command->redir == REDIR_IN)
		vars->fd[0] = open(command->file_in, O_RDONLY);
	if (command->redir == REDIR_OUT_NEW)
		vars->fd[1] = open(command->file_out, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (command->redir == REDIR_OUT_APPEND)
		vars->fd[1] = open(command->file_out, O_CREAT |
		O_APPEND | O_RDWR, 0644);
}

void	iterate_command(t_list *command_list, char **env, t_vars *vars)
{
	pipe(vars->fd);
	if (((t_command*)command_list->content)->redir != NO_REDIR)
		open_files(((t_command*)command_list->content), vars);
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content), vars) == 0 &&
		check_bins(((t_command*)command_list->content), env, vars) == -1)
			vars->ret = 127;
		command_list = command_list->next;
	}
}
