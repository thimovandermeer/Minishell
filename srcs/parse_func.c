/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:04:51 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/30 12:39:34 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator		check_seperator(char *str)
{
	if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (NO_SEP);
}

int				get_length(t_parsing *parser)
{
	int			arg_count;
	t_list		*tmp;

	tmp = parser->list;
	arg_count = 0;
	while (tmp != NULL && !check_seperator(tmp->content))
	{
		arg_count++;
		tmp = tmp->next;
	}
	return (arg_count);
}

t_list			*make_item(int arg_count)
{
	t_command	*command;
	t_list		*tmp;

	command = malloc(sizeof(t_command));
	tmp = ft_lstnew(command);
	command->args = (char**)malloc(sizeof(char *) * (arg_count + 1));
	if (!command->args)
		ft_error("something went wrong creating args\n");
	command->pipe = NO_PIPE;
	return (tmp);
}

void			create_command(t_parsing *parser, t_list **command_list)
{
	int			arg_count;
	t_list		*item;
	int			j;

	arg_count = get_length(parser);
	item = make_item(arg_count);
	if (!item)
		ft_error("something went wrong creating link in list\n");
	j = 0;
	while (parser->list &&
	check_seperator((char *)parser->list->content) == NO_SEP)
	{
		check_redir();
		((t_command*)item->content)->args[j] = parser->list->content;
		parser->list = parser->list->next;
		j++;
	}
	if (parser->cur_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_OUT;
	if (parser->prev_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_IN;
	if (parser->prev_sep == PIPE && parser->cur_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_BOTH;
	ft_lstadd_back(command_list, item);
}

void 			check_redir()
{
	
}

t_list			*parse_line(t_list *list)
{
	t_parsing	parsing;
	t_list		*command_list;

	command_list = NULL;
	parsing.list = list;
	parsing.prev_sep = NO_SEP;
	while (list)
	{
		parsing.cur_sep = check_seperator(list->content);
		if (parsing.cur_sep)
		{
			create_command(&parsing, &command_list);
			parsing.prev_sep = parsing.cur_sep;
			parsing.list = list->next;
		}
		list = list->next;
	}
	if (parsing.list != NULL)
		create_command(&parsing, &command_list);
	return (command_list);
}
