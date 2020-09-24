#include "minishell.h"

int		check_var_name(char *key)
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

void		set_env_name(t_vars *vars, char *argument, char **new_var)
{
	int		index;
	int		loc;
	char	**tmp;
	int		i;

	index = ft_env_len(vars->get_env);
	loc = (find_var_in_env(new_var[0], vars->get_env) > 0) ?
	find_var_in_env(new_var[0], vars->get_env) : index;
	tmp = (char **)malloc(sizeof(char*) * (index + 2));
	if (tmp == NULL)
		printf("error\n"); // normale error message nog inbouwen 
	i = 0;
	while (vars->get_env[i])
	{
		tmp[i] = vars->get_env[i];
		i++;
	}
	tmp[i] = NULL;
	free(vars->get_env);
	vars->get_env = tmp;
	vars->get_env[loc] = ft_strdup(argument);
	vars->get_env[index + 1] = NULL;
}

void		declare_list_thing(t_command *command, t_vars *vars)
{
	int		i;
	size_t	length;
	char	**export_print;

	i = 0;
	length = ft_env_len(vars->get_env);
	export_print = bubblesort(vars->get_env, length);
	while (export_print[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(export_print[i], 1); //" " moet ook worden geprint
		i++;
	}
	free(export_print);
}

int			export_builtin(t_command *command, t_vars *vars)
{
	char	**new_var;
	int		i;

	i = 1;
	while (command->args[i])
	{
		new_var = ft_split(command->args[i], '=');
		if (!check_var_name(new_var[0]))
			printf("Syntax error\n"); // later aanpassen naar goede error message's
		else
			set_env_name(vars, command->args[i], new_var);
		free_array(new_var);
		i++;
	}
	if (i == 1)
		declare_list_thing(command, vars);
	return (0);
}
