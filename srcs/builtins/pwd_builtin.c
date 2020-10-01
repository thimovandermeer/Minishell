/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 13:50:00 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/23 13:27:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int		pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(strerror(errno), 2);
		return (127);
	}
	ft_putendl_fd(cwd, 0);
	return (0);
}
