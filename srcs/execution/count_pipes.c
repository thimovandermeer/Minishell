/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 09:00:01 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/06 11:27:09 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	count_pipes(t_list *list, t_vars *vars)
{
	int		pipes_counter;
	int		cmd;

	pipes_counter = 0;
	cmd = 0;
	while (list)
	{
		if (!ft_strcmp(list->content, "|"))
			pipes_counter++;
		if (!ft_strcmp(list->content, ";"))
		{
			vars->pipes_counter[cmd] = pipes_counter;
			pipes_counter = 0;
			cmd++;
		}
		list = list->next;
	}
	vars->pipes_counter[cmd] = pipes_counter;
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

void	pipes_loop(t_list *list, t_vars *vars)
{
	int		cmd_amount;

	cmd_amount = count_commands(list);
	vars->cmd_amount = cmd_amount;
	vars->pipes_counter = malloc(sizeof(int) * (cmd_amount));
	if (!vars->pipes_counter)
		error_malloc();
	count_pipes(list, vars);
}
