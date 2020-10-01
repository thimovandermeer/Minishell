#include "minishell.h"
#include "libft.h"

/*
**	function which is activated when ctrlc is called and this signals ignores
*/

void		ctrl_c(int signal)
{
	(void)signal;
	ft_putendl_fd("\b\b  ", 1);
	command_prompt();
}

/*
**	function which is activated when esc is called and this signals ignores
*/

void		ctrl_esc(int signal)
{
	(void)signal;
	ft_putstr_fd("\b\b  \b\b", 1);
}
