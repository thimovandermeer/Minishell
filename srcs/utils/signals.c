/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:47:05 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/07 11:23:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>

/*
**	function which is handles when ctrl-c or ctrl-\ is registered
*/

void		signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putendl_fd("\b\b  ", 1);
		command_prompt();
	}
	if (sig_num == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

/*
**	function which activates while in a exec where it shouldn't give a prompt
*/

void		signal_exec(int sig_num)
{
	signal(sig_num, signal_exec);
}

/*
**	function which gives the correct output while in a exec like cat
*/

void		signal_write_exec(t_vars *vars)
{
	if (vars->signal == SIGINT)
		ft_putendl_fd("", 1);
	if (vars->signal == SIGQUIT)
		ft_putendl_fd("Quit: 3", 1);
}
