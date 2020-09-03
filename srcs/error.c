/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 07:22:32 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/02 13:28:51 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	error_general(char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(error_msg, 2);
}

void	error_malloc(void)
{
	error_general("Something went wrong during malloc.");
	exit(1);
}

void	error_invalid_cmd(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": command not found", 2);
}

void	error_syntax(char *arg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("'", 2);
}
