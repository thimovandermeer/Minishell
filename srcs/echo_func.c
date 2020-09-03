/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 14:04:34 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/03 09:12:49 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*create_string(char **tokens)
{
	char	*result;
	int		i;

	i = 1;
	while (tokens[i])
	{
		tokens[i] = ft_strtrim(tokens[i], "\' \"");
		result = ft_strjoin(tokens[i], tokens[i + 1]);
		if (!result)
			error_malloc();
		i++;
	}
	return (result);
}

int		echo_func(t_command *command)
{
	char *str;

	str = create_string(command->args);
	if (command->args[1])
		ft_putstr_fd(str, 1);
	return (1);
}
