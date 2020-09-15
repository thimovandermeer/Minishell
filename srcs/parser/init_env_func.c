/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env_func.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:07:32 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/07 14:43:17 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

size_t 	ft_env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	init_env(char **env, t_vars *vars)
{
	int i;

	vars->get_env = (char **)malloc(sizeof(char *) * (ft_env_len(env) + 1));
	i = 0;
	while (env[i])
	{
		if (!(vars->get_env[i] = ft_strdup(env[i])))
			error_malloc(vars);
		i++;
	}
	env[i] = NULL;
	vars->status = RUNNING;
	vars->err = NO_ERROR;
}