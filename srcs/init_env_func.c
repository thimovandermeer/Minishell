/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env_func.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:07:32 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/23 15:08:11 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t 	ft_env_len(char **envv)
{
	int i;

	i = 0;
	while(envv[i])
		i++;
	return (i);
}

void	init_envv(char **envv)
{
	int i;

	
	get_envv = (char **)malloc(sizeof(char*) * (ft_env_len(envv)+ 1));
	i = 0;
	while (envv[i])
	{
		if (!(get_envv[i] = ft_strdup(envv[i])))
			ft_error("Something went wrong with environment var's"); // dit moet nog aangepast worden naar een goeie error message
		i++;
	}
}
