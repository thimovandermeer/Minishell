/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:54 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 13:46:54 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	function which free's everything inside the command_table
*/

void	free_command_table(t_list **command_list)
{
	t_list		*node;
	t_command	*command;

	node = *command_list;
	while (node)
	{
		command = node->content;
		ft_lstclear(&command->file_in, free_content);
		ft_lstclear(&command->file_out, free_content);
		ft_lstclear(&command->out_mode, free_content);
		free_array(command->args);
		node = node->next;
	}
	ft_lstclear(command_list, free_content);
}

/*
**	function which free's a list and its contents
*/

void	free_list(t_list **list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->content);
		tmp->content = NULL;
	}
	*list = NULL;
}

/*
**	function which free's an string array
*/

void	free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

/*
**	Function which free's content
*/

void	free_content(void *content)
{
	free(content);
}
