/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:41:17 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 13:41:18 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** Driver function for env builtin
*/

int		env_func(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->env[i])
	{
		ft_putendl_fd(vars->env[i], 1);
		i++;
	}
	return (0);
}
