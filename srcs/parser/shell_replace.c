/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_replace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 14:48:51 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/02 14:48:52 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		replace_env(t_vars *vars, char *replace, int i)
{
	int		old_len;
	int		path_len;
	int		rest_len;
	int		new_len;
	char	*new_token;

	old_len = ft_strlen(vars->token);
	path_len = ft_strlen(replace);
	rest_len = old_len - env_len(vars->token + i) - i;
	new_len = i + path_len + rest_len - 1;
	new_token = malloc(sizeof(char) * (new_len + 1));
	if (!new_token)
		error_malloc();
	ft_strlcpy(new_token, vars->token, i);
	ft_strlcat(new_token, replace, i + path_len);
	ft_strlcat(new_token, vars->token + (old_len - rest_len), new_len + 1);
	free(replace);
	free(vars->token);
	vars->token = new_token;
	return (path_len);
}

int		env_len(char *env)
{
	int		len;

	len = 0;
	if (!ft_isalpha(env[len]) && env[len] != '_')
	{
		len++;
		return (len);
	}
	while (ft_isalnum(env[len]) || env[len] == '_')
		len++;
	return (len);
}

char	*find_env(t_vars *vars, int i)
{
	int		len;
	char	*env;
	char	*path;

	len = env_len(vars->token + i);
	env = ft_substr(vars->token, i, len);
	if (!env)
		error_malloc();
	path = get_env(vars->env, env);
	if (!path)
		path = "";
	path = ft_strdup(path);
	if (!path)
		error_malloc();
	free(env);
	return (path);
}
