/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 08:24:47 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/03 08:37:18 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void		ctrl_c(int signal)
{
	(void)signal;
	ft_putendl_fd("\b\b  ", 1);
	command_prompt();
}

void		ctrl_esc(int signal)
{
	(void)signal;
	ft_putstr_fd("\b\b  \b\b", 1);
}
