/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:50:01 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/21 13:10:14 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void		set_env_name(t_vars *vars, char *new_var)
{
	int		index;
	char	**tmp;
	int		i;

	index = ft_env_len(vars->get_env);
	tmp = (char **)malloc(sizeof(char*) * (index + 1));
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
	vars->get_env[index] = ft_strdup(new_var);
}

void		declare_list_thing(t_command *command, t_vars *vars)
{
	int		i;
	int		length;
	char	**export_print;

	i = 0;
	length = ft_env_len(vars->get_env);
	export_print = bubblesort(vars->get_env, length);
	while (export_print[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(export_print[i], 1);
		ft_putchar_fd('\n', 1);
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
			set_env_name(vars, command->args[i]);
		ft_free_array(new_var);
		i++;
	}
	if (i == 1)
		declare_list_thing(command, vars);
	return (0);
}
