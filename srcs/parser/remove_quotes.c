/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:16 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 15:28:34 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**		checks if the new token is smaller than the old one.
**		this function resizes the tokens
*/

void		resize_token(t_vars *vars, int len)
{
	char	*new;
	int		new_len;

	if (len > ft_strlen(vars->token))
	{
		new_len = ft_strlen(vars->token);
		new = malloc(sizeof(char) * (new_len + 1));
		if (!new)
			error_malloc();
		new = ft_memcpy(new, vars->token, new_len);
		new[new_len] = '\0';
		free(vars->token);
		vars->token = new;
	}
}

/*
**		loop which iterates over the old token while new token is being made.
*/

void		quote_loop(char *old, t_vars *vars)
{
	int		i;

	i = 0;
	while (*old)
	{
		if (*old == '\\')
			escape(vars, &i, *old, *(old + 1));
		else if (*old == '\'')
			single_quote(vars, &i, *old);
		else if (*old == '\"')
			double_quote(vars, &i, *old);
		else
		{
			vars->token[i] = *old;
			i++;
		}
		if (*old != '\\' && vars->escape == ESCAPE)
			vars->escape = NO_ESCAPE;
		old++;
	}
	vars->token[i] = '\0';
}

/*
**		this is the driver function for the quote removal
*/

void		remove_quotes(char *old, t_vars *vars)
{
	vars->quote = NO_QUOTE;
	vars->escape = NO_ESCAPE;
	vars->token = malloc(sizeof(char) * (ft_strlen(old) + 1));
	if (!vars->token)
		error_malloc();
	quote_loop(old, vars);
	resize_token(vars, ft_strlen(old));
	free(old);
}
