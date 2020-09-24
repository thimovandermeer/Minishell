
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
		free(temp);
		if (lstat(bin_path, &f) == -1 && bin_path)
			free(bin_path);
		else
		{
			free_array(path);
			return (bin_path);
		}
		i++;
	}
	free_array(path);
	return (NULL);
}

int		check_bins(t_command *command, t_vars *vars, t_exec *exec)
{
	char		**tmp;
	char		*bin_path;
	int			i;

	i = 0;
	while (vars->get_env[i] != '\0')
	{
		tmp = ft_split(vars->get_env[i], '=');
		if (!tmp)
			error_malloc();
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
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
