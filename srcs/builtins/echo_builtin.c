/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 14:04:34 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 09:47:03 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	driver function for echo builtin
*/

int		echo_builtin(t_command *command, t_vars *vars)
{
	int		i;
	int		newline;

	vars->builtin = BUILTIN;
	newline = 1;
	i = 1;
	if (command->args[i] && ft_strcmp(command->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i], 1);
		i++;
		if (command->args[i])
			ft_putchar_fd(' ', 1);
	}
	if (newline == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
