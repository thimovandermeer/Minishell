/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:04:51 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/23 16:12:58 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_seperator(char *str)
{
	if (!ft_strcmp(str, ";"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

t_list 	*parse_line(t_list *list) // return value aanpassen naar linkedlist
{
	int			arg_count;
	int 		j;
	t_list  	*command_list;
	t_command 	*command;
	t_list 		*tmp;
	t_list		*head_command;

	command_list = NULL;
	head_command = list;
	// iterate totdat je een pipe of een puntkomma tegenkomt
	// seperater bouwen en ook redirections checken 
	// 
	while (list)
	{
		head_command = list;
		arg_count = 0;
		while (list && !check_seperator(list->content))
		{
			arg_count++;
			list = list->next;
		}
		command = malloc(sizeof(t_command*));
		command->args = (char**)malloc(sizeof(char *) * (arg_count + 1));
		if (!command->args)
			return (NULL);
		j = 0;
		while (j < arg_count)
		{
			command->args[j] = head_command->content;
			head_command = head_command->next;
			j++;
		}
		command->args[j] = NULL;
		command->pipe = 0; //is stierenschijt, moet nog worden gedaan.
		tmp = ft_lstnew(command);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&command_list, tmp);
		if (list)
			list = list->next;
	}
	return (command_list);
}
