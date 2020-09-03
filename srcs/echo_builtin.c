/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 14:04:34 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/03 17:16:58 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>


int		echo_builtin(t_command *command)
{
	int i;

	i = 1;
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i], 1);
		ft_putstr_fd("\n" ,1);
		i++;
	}
	return (1);
}
