#include "minishell.h"

/*
**	function which checks if the var name is correct
*/

int			check_var_name(char *key)
{
	int	i;

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
	int		i;
	char	*key;
	char	*value;
	i = 0;
	key = ft_substr(export_print, 0, ft_str_pos(export_print, '='));
	value = ft_substr(export_print, ft_str_pos(export_print, '=') + 1, ft_strlen(export_print));
	ft_putstr_fd(key, 1);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('\"', 1);
	ft_putstr_fd(value, 1);
	ft_putchar_fd('\"', 1);
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

	i = 1;
	while (command->args[i])
	{
		new_var = ft_split(command->args[i], '=');
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
