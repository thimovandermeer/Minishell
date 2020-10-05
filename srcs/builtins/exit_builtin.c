/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:24 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 13:46:29 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**		Function which checks if the str is digits only
*/

int		str_is_num(char *str)
{
	int		i;

	if (!str)
		return (1);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
**		Gets callled when there is an invalid argument (not numeric)
*/

int		exit_invalid_arguments(t_command *command)
{
	if (command->pipe == NO_PIPE)
		ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(command->args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	if (command->pipe == NO_PIPE)
		exit(255);
	return (1);
}

/*
**		Gets called when there are too many arguments
*/

int		exit_multiple_arguments(t_command *command, t_vars *vars)
{
	if (command->pipe == NO_PIPE)
		ft_putendl_fd("exit", 2);
	error_general("exit: too many arguments", vars);
	return (1);
}

/*
**		Driver function for exit builtin
*/

int		exit_builtin(t_command *command, t_vars *vars)
{
	int		i;

	vars->builtin = BUILTIN;
	i = 1;
	while (command->args[i])
	{
		if (i > 1)
			return (exit_multiple_arguments(command, vars));
		if (!str_is_num(command->args[i]))
			return (exit_invalid_arguments(command));
		i++;
	}
	if (command->pipe == NO_PIPE)
		vars->status = STOP;
	if (command->args[1])
		return (ft_atoi(command->args[1]));
	return (0);
}
