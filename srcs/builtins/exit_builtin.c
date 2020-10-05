/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:24 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 10:57:54 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	Function which checks if the str is digits only
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
**	Driver function for echo builtin
*/

int		exit_builtin(t_command *command, t_vars *vars)
{
	int		i;

	vars->builtin = BUILTIN;
	i = 1;
	while (command->args[i])
	{
		if (i > 1)
		{
			ft_putendl_fd("exit", 2);
			error_general("exit: too many arguments", vars);
			return (1);
		}
		if (!str_is_num(command->args[i]))
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(command->args[i], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(1);
		}
		i++;
	}
	if (command->pipe == NO_PIPE)
		vars->status = STOP;
	if (command->args[1])
		return (ft_atoi(command->args[1]));
	return (0);
}
