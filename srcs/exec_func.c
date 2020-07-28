/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:00:03 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/28 14:29:31 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		check_bins(t_command *command, char **env)
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
				return (ft_executable(bin_path, command, env));
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

void 	redirections(t_command *command)
{
	pipe(command->fd);
	if (command->pipe == PIPE_IN)
	{
		dup2(command->fd[1], 1);
		close(command->fd[0]);
	}
	if (command->pipe == PIPE_OUT)
	{
		close(command->fd[1]);
		dup2(command->fd[0], 0);
	}
}

int 	ft_executable(char *bin_path, t_command *command, char **env)
{
	pid_t p_id;

	// redirection handling and pipe handling
	// redirections(command);
	p_id = fork();
	if (p_id == 0)
		return (execve(bin_path, command->args, env));
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(&p_id);
	return (0);
}

void iterate_command(t_list *command_list, char **env)
{
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content)) == 0 && check_bins(((t_command*)command_list->content), env) == -1)
			ft_error("Some sort of error message\n"); // deze nog even goed maken 
		command_list = command_list->next;
	}
}