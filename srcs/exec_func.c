/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:00:03 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/30 11:38:37 by thimovander   ########   odam.nl         */
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

int 	ft_executable(char *bin_path, t_command *command, char **env, t_vars *vars)
{
	pid_t p_id;

	p_id = fork();
	if (p_id == 0)
	{
		if (command->pipe == PIPE_OUT)
		{
			dup2(vars->fd[1], 1);
			close(vars->fd[0]);
			return (execve(bin_path, command->args, env));
		}
		else if (command->pipe == PIPE_IN)
		{
			dup2(vars->fd[0], 0);
			return (execve(bin_path, command->args, env));
		}
		else
			return (execve(bin_path, command->args, env));
	}
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(NULL);
	close(vars->fd[1]);
	return (0);
}

void iterate_command(t_list *command_list, char **env)
{
	t_vars 	vars;
	pipe(vars.fd);
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content)) == 0 && check_bins(((t_command*)command_list->content), env, &vars) == -1)
			ft_error("Some sort of error message\n"); // deze nog even goed maken 
		command_list = command_list->next;
	}
}