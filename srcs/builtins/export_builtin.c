/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:50:01 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/17 18:44:54 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// temporary func delete later

void		print_env_list(char **get_env)
{
	int i;

	i = 0;
	while (get_env[i])
	{
		printf("%s\n", get_env[i]);
		i++;
	}
	printf("END OF LIST\n");
}

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

void		resize_env(int index, char *new_var, t_vars *vars)
{
	char	**tmp;
	int		i;

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

void		set_env_name(t_vars *vars, char *new_var)
{
	int		index;
	char	**tmp;

	index = ft_env_len(vars->get_env);
	// resize env list
	resize_env(index, new_var, vars);
	

	// put this var under it
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
   		// free var array after wards
		ft_free_array(new_var);
   		// print the export out
		i++;
	}
	if (i == 1)
		declare_list_thing();
    return (0);
}
