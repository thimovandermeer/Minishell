/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_expansion_status.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 14:48:35 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/02 14:48:36 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
**	$ is found and replaces it for the path
*/

int		shell_sign(t_vars *vars, int i)
{
	char	*tmp;

	if (vars->quote == SINGLE_QUOTE || vars->escape == ESCAPE)
		return (0);
	if (vars->token[i + 1] == '\0')
		return (0);
	else if (vars->token[i + 1] == '?')
	{
		tmp = ft_itoa(vars->ret);
		if (!tmp)
			error_malloc();
	}
	else
		tmp = find_env(vars, i + 1);
	return (replace_env(vars, tmp, i + 1) - 1);
}

void	shell_double_quote(t_vars *vars)
{
	if (vars->quote == NO_QUOTE && vars->escape != ESCAPE)
		vars->quote = DOUBLE_QUOTE;
	else if (vars->quote == DOUBLE_QUOTE && vars->escape != ESCAPE)
		vars->quote = NO_QUOTE;
}

void	shell_single_quote(t_vars *vars)
{
	if (vars->quote == NO_QUOTE && vars->escape != ESCAPE)
		vars->quote = SINGLE_QUOTE;
	else if (vars->quote == SINGLE_QUOTE)
		vars->quote = NO_QUOTE;
}

void	shell_escape(t_vars *vars)
{
	if (vars->escape == ESCAPE)
		vars->escape = NO_ESCAPE;
	if (vars->quote != SINGLE_QUOTE)
		vars->escape = ESCAPE;
}
