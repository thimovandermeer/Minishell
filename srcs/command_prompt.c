/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 14:03:50 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/05 14:03:54 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		command_prompt();
		signal(SIGINT, command_handler);
	}
}

void	fork_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		signal(SIGINT, fork_handler);
	}
}

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
	ft_putstr_fd("\033[32m--->\033[0m$", 1);
}
