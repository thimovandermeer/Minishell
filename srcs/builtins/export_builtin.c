/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:30 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 09:49:49 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	function which checks if the var name is correct
*/

int			check_var_name(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

/*
**	function which sets the env name to the new value
*/

void		set_env_name(t_vars *vars, char *argument, char **new_var)
{
	int		index;
	int		loc;
	char	**tmp;
	int		i;

	index = ft_env_len(vars->env);
	loc = (find_var_in_env(new_var[0], vars->env) > 0) ?
	find_var_in_env(new_var[0], vars->env) : index;
	tmp = (char **)malloc(sizeof(char*) * (index + 2));
	if (tmp == NULL)
		error_malloc();
	i = 0;
	while (vars->env[i])
	{
		tmp[i] = vars->env[i];
		i++;
	}
	tmp[i] = NULL;
	free(vars->env);
	vars->env = tmp;
	free(vars->env[loc]);
	vars->env[loc] = ft_strdup(argument);
	vars->env[index + 1] = NULL;
}

/*
**	function which sets the quotation marks for export call
*/

void		set_quotes(char *export_print)
{
	int		split_index;
	int		value_len;
	char	*key;
	char	*value;

	split_index = ft_str_pos(export_print, '=');
	if (split_index == 0)
		split_index = ft_strlen(export_print);
	value_len = ft_strlen(export_print) - split_index;
	key = ft_substr(export_print, 0, split_index);
	value = ft_substr(export_print, split_index + 1, value_len);
	ft_putstr_fd(key, 1);
	if (split_index == ft_str_pos(export_print, '='))
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		ft_putstr_fd(value, 1);
		ft_putchar_fd('\"', 1);
	}
	ft_putchar_fd('\n', 1);
	free(key);
	free(value);
}

/*
**	function which creates the output for the export call without arguments
*/

void		declare_list_thing(t_command *command, t_vars *vars)
{
	int		i;
	size_t	length;
	char	**export_print;

	i = 0;
	length = ft_env_len(vars->env);
	export_print = bubblesort(vars->env, length);
	while (export_print[i])
	{
		ft_putstr_fd("declare -x ", 1);
		set_quotes(export_print[i]);
		i++;
	}
	free_array(export_print);
}

/*
**	Driver function for export builtin
*/

int			export_builtin(t_command *command, t_vars *vars)
{
	char	**new_var;
	int		i;

	vars->builtin = BUILTIN;
	i = 1;
	while (command->args[i])
	{
		new_var = ft_split(command->args[i], '=');
		if (!new_var)
			error_malloc();
		if (!check_var_name(new_var[0]))
			error_identifier(command->args, vars);
		else
			set_env_name(vars, command->args[i], new_var);
		free_array(new_var);
		i++;
	}
	if (i == 1)
		declare_list_thing(command, vars);
	return (0);
}
