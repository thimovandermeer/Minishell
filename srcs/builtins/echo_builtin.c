/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 14:04:34 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/07 15:44:28 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		echo_builtin(t_command *command)
{
	int		i;
	int		newline;

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
