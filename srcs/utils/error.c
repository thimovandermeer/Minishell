#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	error_general(char *error_msg, t_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(error_msg, 2);
	vars->ret = 127;
}

void	error_malloc(void)
{
	ft_putendl_fd("Something went wrong during malloc.", 2);
	exit(1);
}

void	error_invalid_cmd(char *arg, t_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": command not found", 2);
	vars->ret = 127;
}

void	error_syntax(char *arg, t_vars *vars)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("'", 2);
	vars->ret = 127;
}
