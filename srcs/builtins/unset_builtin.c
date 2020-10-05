/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:41 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 09:50:31 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	function which returns the exact position of the
**	searched for env name in the environment list
*/

int		find_var_in_env(char *search_var, char **tmp_env)
{
	int		i;
	char	**search_place;

	i = 0;
	while (tmp_env[i])
	{
		search_place = ft_split(tmp_env[i], '=');
		if (search_place == NULL)
			error_malloc();
		if (!ft_strcmp(search_place[0], search_var))
		{
			free_array(search_place);
			return (i);
		}
		free_array(search_place);
		i++;
	}
	return (-1);
}

/*
**	function which recreate the env list with the new size
*/

void	recreate_env_list(t_vars *vars, int index, int skip_loc)
{
	free(vars->env[skip_loc]);
	while (skip_loc < index)
	{
		vars->env[skip_loc] = vars->env[skip_loc + 1];
		skip_loc++;
	}
	vars->env[skip_loc] = NULL;
}

/*
**	Driver function for the unset builtin function
*/

int		unset_builtin(t_vars *vars, t_command *command)
{
	int		i;
	size_t	index;
	int		skip_loc;

	vars->builtin = BUILTIN;
	i = 1;
	while (command->args[i])
	{
		skip_loc = find_var_in_env(command->args[i], vars->env);
		if (skip_loc >= 0)
		{
			index = ft_env_len(vars->env) - 1;
			recreate_env_list(vars, index, skip_loc);
		}
		else
		{
			error_identifier(command->args, vars);
			break ;
		}
		i++;
	}
	return (0);
}
