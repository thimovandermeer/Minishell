#include "minishell.h"
#include "libft.h"

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
