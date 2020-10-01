#include "minishell.h"
#include "libft.h"

/*
** Driver function for env builtin
*/

int		env_func(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->env[i])
	{
		ft_putendl_fd(vars->env[i], 1);
		i++;
	}
	return (0);
}
