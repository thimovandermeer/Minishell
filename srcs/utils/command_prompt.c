#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*
**	this function is activated if the system gives a command signal
*/

void	command_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		command_prompt();
		signal(SIGINT, command_handler);
	}
}

/*
**	this function is activated if the system gives a fork signal
*/

void	fork_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		signal(SIGINT, fork_handler);
	}
}

/*
**	this function creates the command prompt
*/

void	command_prompt(void)
{
	char *cwd;
	char *home_cwd;
	char buff[4096 + 1];
	char *test;

	test = ft_strdup("~");
	cwd = getcwd(buff, 4096);
	home_cwd = ft_strjoin(test, cwd);
	ft_putstr_fd(home_cwd, 1);
	free(home_cwd);
	free(test);
	ft_putstr_fd("\033[32m--->\033[0m$ ", 1);
}
