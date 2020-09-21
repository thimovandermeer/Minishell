/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:49:47 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/17 18:10:00 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_func(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->get_env[i])
	{
		ft_putstr_fd(vars->get_env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
