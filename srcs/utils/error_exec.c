/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:26:21 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/02 11:30:13 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function gives a invalid command messages when called
*/

void	error_str_error(char *arg, char *str_error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str_error, 2);
}
