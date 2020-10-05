/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:01 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 09:44:19 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
**	function which sets pwd to the right path
*/

void	set_pwd(t_vars *vars, int var_index, char *env_var, char *loc)
{
	free(vars->env[var_index]);
	vars->env[var_index] = NULL;
	vars->env[var_index] = ft_strjoin(env_var, loc);
	if (!vars->env[var_index])
		error_malloc();
}

/*
**	function which updates pwd when there has been a change in directory
*/

void	update_pwd(t_vars *vars, char *new_pwd)
{
	char	*old_pwd;
	int		index_pwd;

	old_pwd = get_env(vars->env, "PWD");
	if (!old_pwd)
		old_pwd = "";
	index_pwd = find_var_in_env("OLDPWD", vars->env);
	if (index_pwd >= 0)
		set_pwd(vars, index_pwd, "OLDPWD=", old_pwd);
	index_pwd = find_var_in_env("PWD", vars->env);
	if (index_pwd == -1)
		return ;
	set_pwd(vars, index_pwd, "PWD=", new_pwd);
}

/*
**	function which sets current dir to forgoing dir
*/

int		cd_old(t_vars *vars)
{
	char	*old_pwd;
	char	*tmp;

	old_pwd = get_env(vars->env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		return (1);
	}
	tmp = ft_strdup(old_pwd);
	if (!tmp)
		error_malloc();
	ft_putendl_fd(old_pwd, 1);
	update_pwd(vars, tmp);
	free(tmp);
	return (0);
}

/*
**	function which cd's to home directory
*/

int		cd_home(t_vars *vars)
{
	char	*tmp;

	tmp = get_env(vars->env, "HOME");
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
	update_pwd(vars, get_env(vars->env, "HOME"));
	return (0);
}

/*
**	driver function for cd builtin function
*/

int		cd_builtin(t_command *command, t_vars *vars)
{
	char	new_cwd[PATH_MAX];

	vars->builtin = BUILTIN;
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
