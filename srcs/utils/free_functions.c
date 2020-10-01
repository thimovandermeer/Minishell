#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

// free path

// free command_list

/*
**	function which free's everything inside the command_table
*/

void	free_command_table(t_list **command_list)
{
	t_list *node;
	t_command *command;

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

// free_args_array

void 	free_array(char **arr)
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

// free_environment

/*
**	free command struct
*/

void	free_command_struct(t_command *command)
{
	
}

/*
**	Function which free's content
*/

void	free_content(void *content)
{
	free(content);
}
