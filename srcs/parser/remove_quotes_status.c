/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_status.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:11 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 15:26:28 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
**		determines if the " should be placed when it found a "
*/

void		double_quote(t_vars *vars, int *i, char c)
{
	if (vars->quote == NO_QUOTE && vars->escape != ESCAPE)
		vars->quote = DOUBLE_QUOTE;
	else if (vars->quote == DOUBLE_QUOTE && vars->escape != ESCAPE)
		vars->quote = NO_QUOTE;
	else if (vars->quote == SINGLE_QUOTE || vars->escape == ESCAPE)
	{
		vars->token[*i] = c;
		(*i)++;
	}
}

/*
**		determines if the ' should be placed when it found a '
*/

void		single_quote(t_vars *vars, int *i, char c)
{
	if (vars->quote == NO_QUOTE && vars->escape != ESCAPE)
		vars->quote = SINGLE_QUOTE;
	else if (vars->quote == SINGLE_QUOTE)
		vars->quote = NO_QUOTE;
	else if (vars->quote == DOUBLE_QUOTE || vars->escape == ESCAPE)
	{
		vars->token[*i] = c;
		(*i)++;
	}
}

/*
**		determines if the \ should be placed when it found a \
*/

void		escape(t_vars *vars, int *i, char c, char special)
{
	if (vars->quote == SINGLE_QUOTE)
	{
		vars->token[*i] = c;
		(*i)++;
	}
	else if (vars->escape == ESCAPE)
	{
		vars->token[*i] = c;
		(*i)++;
		vars->escape = NO_ESCAPE;
	}
	else if (vars->quote == DOUBLE_QUOTE)
	{
		vars->escape = ESCAPE;
		if (!ft_strchr("$`\"\\", special))
		{
			vars->token[*i] = c;
			(*i)++;
		}
	}
	else
		vars->escape = ESCAPE;
}
