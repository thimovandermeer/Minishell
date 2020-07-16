/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 10:59:33 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/16 11:00:14 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*get_env_var(char *str)
{
	int 	i;
	char 	*tmp;

	i = 0;
	while(get_envv[i])
	{
		tmp = ft_strjoin()
	}
}

void 	home_path(char *path)
{
	char *home_path;

	if (!path)
		return (NULL);
	home_path = get_env_var("HOME");
	
}

void 	command_prompt()
{
	char *cwd;
	char buff[500];

	cwd = getcwd(buff, 500);
	get_env_var();
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\033[32m--->\033", 1);
}
