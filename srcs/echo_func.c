/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 15:49:42 by thimovander   #+#    #+#                 */
/*   Updated: 2020/08/04 11:09:37 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_string(char **tokens)
{
	char	*result;
	int		i;

	i = 1;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "$"))
		tokens[i] = ft_strtrim(tokens[i], "\' \"");
		result = ft_strjoin(tokens[i], tokens[i + 1]);
		i++;
	}
	return (result);
}

int		echo_func(t_command *command)
{
	char *str;

	str = create_string(command->args);
	if (command->args == NULL)
		write(1, "\n", 1);
	else
		ft_putstr_fd(str, 1);
	return (0);
}
