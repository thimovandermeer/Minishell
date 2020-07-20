/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:49:42 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/16 15:21:03 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_func(char *token)
{
	int i;

	i = 0;
	if (token == NULL)
		write(1, "\n", 1);
	else
	{
		ft_putstr_fd(token, 1);
		write(1, "\n", 1);
	}
	return (1);
}