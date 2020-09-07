/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 13:50:00 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/07 13:53:27 by thimovander   ########   odam.nl         */
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
		exit(1); //niet exit
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
