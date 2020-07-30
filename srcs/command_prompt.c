/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 10:59:33 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/27 12:38:19 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    command_handler(int sig_num)
{
    if (sig_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        command_prompt();
        signal(SIGINT, command_handler);
    }
}

void    fork_handler(int sig_num)
{
    if (sig_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        signal(SIGINT, fork_handler);
    }
}
void 	command_prompt()
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
