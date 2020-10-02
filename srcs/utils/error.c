/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:47 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 13:46:47 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function displays a general error message when called
*/

void	error_general(char *error_msg, t_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(error_msg, 2);
	vars->ret = 127;
}

/*
**	this function gives a malloc error message when called
*/

void	error_malloc(void)
{
	ft_putendl_fd("Something went wrong during malloc.", 2);
	exit(1);
}

/*
**	this function gives a invalid command messages when called
*/

void	error_invalid_cmd(char *arg, t_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": command not found", 2);
	vars->ret = 127;
}

/*
**	this function gives a syntax error when called
*/

void	error_syntax(char *arg, t_vars *vars)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("'", 2);
	vars->ret = 127;
}

/*
**	this function gives a identifier error when called
*/

void	error_identifier(char **arg, t_vars *vars)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putendl_fd(": not a valid identifier", 2);
}
