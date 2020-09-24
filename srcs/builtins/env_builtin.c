#include "minishell.h"
#include "libft.h"

int		env_func(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->get_env[i])
	{
		ft_putendl_fd(vars->get_env[i], 1);
		i++;
	}
	return (0);
}
