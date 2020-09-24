#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		str_is_num(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		exit_builtin(t_command *command, t_vars *vars)
{
	int		i;

	i = 1;
	while (command->args[i])
	{
		if (i > 1)
		{
			ft_putendl_fd("exit", 2);
			error_general("exit: too many arguments", vars);
			return (1);
		}
		if (!str_is_num(command->args[i]))
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(command->args[i], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(1);
		}
		i++;
	}
	vars->status = STOP;
	return (0);
}
