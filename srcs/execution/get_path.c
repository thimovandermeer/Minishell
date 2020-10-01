
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
**	function which creates a new bin_path when found
*/

char	*create_new_binpath(char **path, char *token, int i)
{
	char		*temp;
	char		*bin_path;
	struct stat	f;

	temp = ft_strjoin(path[i], "/");
	bin_path = ft_strjoin(temp, token);
	free(temp);
	if (lstat(bin_path, &f) == -1 && bin_path)
		free(bin_path);
	else
	{
		free_array(path);
		return (bin_path);
	}
	return (NULL);
}

/*
**	function which splits the bin path and searches
**	on different locations for an executable
*/

char	*get_bin_path(char *tmp, char *token)
{
	char			**path;
	char			*bin_path;
	int				i;

	path = ft_split(tmp, ':');
	if (!path)
		error_malloc();
	i = 0;
	while (path[i])
	{
		bin_path = create_new_binpath(path, token, i);
		if (bin_path != NULL)
			return (bin_path);
		i++;
	}
	free_array(path);
	return (NULL);
}

/*
**	function which iterates al environment variables
**	searching for the path variable to start searching on these locations
*/

int		check_bins(t_command *command, t_vars *vars, t_exec *exec)
{
	char		**tmp;
	char		*bin_path;
	int			i;

	i = 0;
	while (vars->env[i])
	{
		tmp = ft_split(vars->env[i], '=');
		if (!tmp)
			error_malloc();
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			free(exec->bin_path);
			exec->bin_path = get_bin_path(tmp[1], command->args[0]);
			free_array(tmp);
			if (!exec->bin_path)
				return (0);
			return (1);
		}
		i++;
		free_array(tmp);
	}
	return (0);
}
