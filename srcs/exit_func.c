/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:49:56 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/03 08:15:44 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exit_func(t_command *command, t_vars *vars)
{
	if (command->pipe == NO_PIPE)
	{
		vars->status = 0;
		return (0);
	}
	return (1);
}
