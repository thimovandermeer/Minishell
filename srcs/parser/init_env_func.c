/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env_func.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:45:59 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/02 14:37:17 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
**	this function returns the length of the current environment list
*/

size_t		ft_env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
**	this function initiates the new environment
*/

void		init_env(char **env, t_vars *vars)
{
	int i;

	vars->env = (char **)malloc(sizeof(char *) * (ft_env_len(env) + 1));
	i = 0;
	while (env[i])
	{
		vars->env[i] = ft_strdup(env[i]);
		if (!vars->env[i])
			error_malloc();
		i++;
	}
	env[i] = NULL;
	vars->status = RUNNING;
}

/*
**	this function searches for the var name
**	in the current environment variables
*/

char		*search_var_name(char *search_val, char **search_place)
{
	int		i;
	char	**key_pair;
	char	*replace_value;
	int		len;

	i = 0;
	while (search_place[i])
	{
		key_pair = ft_split(search_place[i], '=');
		len = ft_strlen(key_pair[0]);
		if (!ft_strncmp(key_pair[0], search_val, len))
		{
			replace_value = ft_strdup(key_pair[1]);
			return (replace_value);
		}
		i++;
	}
	return (NULL);
}

/*
**	this function checks the quote type
*/

t_quote		check_quote_type(t_list *list)
{
	t_quote		quote;

	quote = NO_QUOTE;
	if (ft_strchr(list->content, '\"'))
		quote = DOUBLE_QUOTE;
	else if (ft_strchr(list->content, '\''))
		quote = SINGLE_QUOTE;
	return (quote);
}
