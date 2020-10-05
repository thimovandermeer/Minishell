/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:47:05 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/05 07:22:19 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>

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

/*
**	function which activates our signal handling
*/

void		signal_activation(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_esc);
}
