#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	double_quote(t_vars *vars, int *i, char c)
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

static void	single_quote(t_vars *vars, int *i, char c)
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

static void	escape(t_vars *vars, int *i, char c, char special)
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

void		remove_quotes(char *old, t_vars *vars)
{
	int		i;

	vars->token = malloc(sizeof(char) * (ft_strlen(old) + 1));
	if (!vars->token)
		error_malloc();
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
