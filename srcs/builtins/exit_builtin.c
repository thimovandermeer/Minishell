/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:49:56 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/03 11:18:05 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     exit_builtin(t_command *command, t_vars *vars)
{
	if (command->pipe == NO_PIPE)
	{
		vars->status = STOP;
		return (0);
	}
	//WORK IN PROGRESS
	return (1);
}
