/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:00:03 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/23 15:01:12 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  check_bins(char **tokens, char **env)
{
	char 			**tmp;
	char 			**path;
	char 			*bin_path;
	struct stat		f; // check https://man7.org/linux/man-pages/man2/stat.2.html voor uitleg
	int 			i;
	i = 0;
	printf("allemaal biins heeee\n");
	//  int lstat(const char *pathname, struct stat *statbuf);
	while (get_envv[i] != '\0')
	{
		tmp = ft_split(get_envv[i], '=');
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			int j;
			j = 0;
			path = ft_split(tmp[1], ':');
			while (path[j])
			{
				path[j] = ft_strjoin(path[j], "/");
				bin_path = ft_strjoin(path[j], tokens[0]);
				if (lstat(bin_path, &f) == -1)
					free(bin_path);
				else
					return (ft_executable(bin_path, f, tokens, env)); // vervolgend executable opstarten he met fork en de hele tering zooi
				j++;
			}
		}
		i++;
	}
	return (-1);
}

int 	ft_executable(char *bin_path, struct stat f,char **tokens, char **env)
{
	pid_t p_id;

	(void)f;
	p_id = fork();
	printf("binpath = %s\n", bin_path);
	if (p_id == 0)
		return (execve(bin_path, tokens, env));
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(&p_id); // dit zorgt ervoor dat the main proces niet door gaat totdat the child proces klaar is
	// signal handling ???? hier zometeen nog naar kijken
	// wat zijn de return values van fork ? kan hier ook iets in fout gaan? zo ja hoe ga ik dit fixen?
	// inprincipe als ik geen error krijg op fork kan ik execve aanroepen
	return (0);
}

void iterate_command(t_list *command_list, char **env)
{

	// printf("command = %s\n", ((t_command*)command_list->content)->args[0]);
	// vanaf hier moet het blijven staan zoals het staat dus die commands moeten de structuur zijn en die tokens[0] moeten daaronder gehakt worden.
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content)->args) == 0 && check_bins(((t_command*)command_list->content)->args, env) == -1)
			ft_error("Some sort of error message\n"); // deze nog even goed maken 
		command_list = command_list->next;
	}
}