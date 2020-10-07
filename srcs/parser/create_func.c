/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_func.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:45:32 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/06 15:00:25 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function makes a new item for the command struct
*/

t_list			*make_item(int arg_count, t_vars *vars)
{
	t_command	*command;
	t_list		*tmp;

	command = malloc(sizeof(t_command));
	if (!command)
		error_malloc();
	tmp = ft_lstnew(command);
	if (!tmp)
		error_malloc();
	command->args = (char**)malloc(sizeof(char *) * (arg_count + 1));
	if (!command->args)
		error_malloc();
	command->args[arg_count] = NULL;
	command->pipe = NO_PIPE;
	command->file_in = NULL;
	command->file_out = NULL;
	command->out_mode = NULL;
	return (tmp);
}

/*
**	this creates the commandlist
*/

void			create_command(t_parsing *parser, t_list **command_list,
								t_vars *vars)
{
	int		arg_count;
	t_list	*command;

	arg_count = get_length(parser);
	command = make_item(arg_count, vars);
	parse_command((t_command*)command->content, parser, vars);
	ft_lstadd_back(command_list, command);
}

/*
**	this function add's the new command token to the end of the list
*/

void			add_list(t_list **list, void *content)
{
	t_list		*new_item;

	new_item = ft_lstnew(content);
	if (!new_item)
		error_malloc();
	ft_lstadd_back(list, new_item);
}
