/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_func.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:45:36 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 13:45:36 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	function which iterates over the token to search for $
*/

void		shell_expansion(t_vars *vars, char *old)
{
	int		i;

	vars->token = ft_strdup(old);
	if (!vars->token)
		error_malloc();
	vars->quote = NO_QUOTE;
	vars->escape = NO_ESCAPE;
	i = 0;
	while (vars->token[i])
	{
		if (vars->token[i] == '\\')
			shell_escape(vars);
		else if (vars->token[i] == '\'')
			shell_single_quote(vars);
		else if (vars->token[i] == '\"')
			shell_double_quote(vars);
		else if (vars->token[i] == '$')
			i += shell_sign(vars, i);
		if (vars->token[i] != '\\' && vars->escape == ESCAPE)
			vars->escape = NO_ESCAPE;
		i++;
	}
	free(old);
}

/*
**	processes every content and updates it to its final command form
*/

void		expand_loop(t_list *list, t_vars *vars)
{
	while (list && ft_strcmp(list->content, ";"))
	{
		shell_expansion(vars, list->content);
		remove_quotes(vars->token, vars);
		list->content = vars->token;
		list = list->next;
	}
}
