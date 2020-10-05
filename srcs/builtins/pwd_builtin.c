/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 13:50:00 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/05 09:50:48 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
**	Driver function for pwd builtin
*/

int		pwd_builtin(t_vars *vars)
{
	char	cwd[PATH_MAX];

	vars->builtin = BUILTIN;
	ft_bzero(cwd, PATH_MAX);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(strerror(errno), 2);
		return (127);
	}
	ft_putendl_fd(cwd, 0);
	return (0);
}
