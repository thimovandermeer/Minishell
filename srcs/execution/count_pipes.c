/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 09:00:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/06 09:28:22 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	count_pipes(t_list *list, t_vars *vars)
{
	int		pipes;
	int		cmd;

	pipes = 0;
	cmd = 0;
	while (list)
	{
		if (!ft_strcmp(list->content, "|"))
			pipes++;
		if (!ft_strcmp(list->content, ";"))
		{
			printf("cmd: [%i] pipes: [%i]\n", cmd, pipes);
			vars->pipes[cmd] = pipes;
			pipes = 0;
			cmd++;
		}
		list = list->next;
	}
	printf("cmd: [%i] pipes: [%i]\n", cmd, pipes);
	vars->pipes[cmd] = pipes;
}

int		count_commands(t_list *list)
{
	int		amount;

	amount = 1;
	while (list)
	{
		if (!ft_strcmp(list->content, ";"))
			amount++;
		if (!ft_strcmp(list->content, ";") && !list->next)
			amount--;
		list = list->next;
	}
	return (amount);
}

void		pipes_loop(t_list *list, t_vars *vars)
{
	int		cmd_amount;

	cmd_amount = count_commands(list);
	vars->pipes = malloc(sizeof(int) * (cmd_amount));
	if (!vars->pipes)
		error_malloc();
	count_pipes(list, vars);
}
