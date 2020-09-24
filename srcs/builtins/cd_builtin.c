#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	update_pwd(t_vars *vars, char *new_pwd)
{
	char	*old_pwd;
	int		index_pwd;

	old_pwd = get_env(vars->get_env, "PWD");
	if (!old_pwd)
		old_pwd = "";
	printf("getcwd: [%s]\n", old_pwd);
	index_pwd = find_var_in_env("OLDPWD", vars->get_env);
	if (index_pwd >= 0)
	{
		free(vars->get_env[index_pwd]);
		vars->get_env[index_pwd] = NULL;
		vars->get_env[index_pwd] = ft_strjoin("OLDPWD=", old_pwd);
		if (!vars->get_env[index_pwd])
			error_malloc();
	}
	index_pwd = find_var_in_env("PWD", vars->get_env);
	if (index_pwd == -1)
		return ;
	free(vars->get_env[index_pwd]);
	vars->get_env[index_pwd] = NULL;
	vars->get_env[index_pwd] = ft_strjoin("PWD=", new_pwd);
	if (!vars->get_env[index_pwd])
		error_malloc();
}

int		cd_old(t_vars *vars)
{
	char	*old_pwd;

	old_pwd = get_env(vars->get_env, "OLDPWD");
	printf("old_pwd: [%s]\n", old_pwd);
	if (!old_pwd)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		return (1);
	}
	update_pwd(vars, old_pwd);
	return (0);
}

int		cd_home(t_vars *vars)
{
	char	*tmp;

	tmp = get_env(vars->get_env, "HOME");
	if (!tmp)
	{
		ft_putendl_fd("HOME not set", 2);
		return (1);
	}
	else if (chdir(tmp) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	update_pwd(vars, get_env(vars->get_env, "HOME"));
	return (0);
}

int		cd_builtin(t_command *command, t_vars *vars)
{
	char	new_cwd[PATH_MAX];

	printf("OLDPWD: [%s]\n", get_env(vars->get_env, "OLDPWD"));
	if (!command->args[1])
		return (cd_home(vars));
	else if (!ft_strcmp(command->args[1], "-"))
		return (cd_old(vars));
	if (chdir(command->args[1]) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_bzero(new_cwd, PATH_MAX);
	if (!getcwd(new_cwd, sizeof(new_cwd)))
	{
		ft_putendl_fd(strerror(errno), 2);
		return (127);
	}
	update_pwd(vars, new_cwd);
	return (0);
}
