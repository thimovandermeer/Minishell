/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_func.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 13:50:28 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/02 07:40:38 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	cd_home(char **env)
{
	char	*tmp;

	tmp = get_env(env, "HOME");
	if (!tmp)
		ft_putstr_fd("HOME not set\n", 2);
	else if (chdir(tmp) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

int		cd_func(t_command *command, char **env)
{
	if (!command->args[1])
		cd_home(env);
	else if (chdir(command->args[1]) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}
