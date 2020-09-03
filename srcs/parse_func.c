/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:04:51 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/03 14:35:45 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

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
	int				arg_count;
	t_list			*tmp;
	t_redirection	current;
	t_redirection	prev;

	prev = NO_REDIR;
	tmp = parser->list;
	arg_count = 0;
	while (tmp && check_seperator(tmp->content) == NO_SEP)
	{
		arg_count++;
		prev = current;
		current = check_redir(tmp->content);
		if (current != NO_REDIR)
			arg_count -= 2;
		if (prev != NO_REDIR && current != NO_REDIR)
			return (0);
		tmp = tmp->next;
	}
	if (current != NO_REDIR)
		return (0);
	return (arg_count);
}

t_list			*make_item(int arg_count)
{
	t_command	*command;
	t_list		*tmp;

	command = malloc(sizeof(t_command));
	if (!command)
		error_malloc();
	tmp = ft_lstnew(command);
	if (!tmp)
	{
		free(command);
		error_malloc();
	}
	command->args = (char**)malloc(sizeof(char *) * (arg_count + 1));
	if (!command->args)
	{
		ft_free_array(command->args);
		error_malloc();
	}
	command->args[arg_count] = NULL;
	command->pipe = NO_PIPE;
	command->redir = NO_REDIR;
	return (tmp);
}

t_redirection	check_redir(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (REDIR_OUT_NEW);
	if (!ft_strcmp(str, ">>"))
		return (REDIR_OUT_APPEND);
	return (NO_REDIR);
}

void			redir_handling(t_parsing *parser, t_list *item)
{
	char *file;

	file = parser->list->next->content;
	if (parser->redir == REDIR_IN)
	{
		((t_command*)item->content)->file_in = file;
		((t_command*)item->content)->redir = REDIR_IN;
	}
	if (parser->redir == REDIR_OUT_NEW)
	{
		((t_command*)item->content)->file_out = file;
		((t_command*)item->content)->redir = REDIR_OUT_NEW;
	}
	if (parser->redir == REDIR_OUT_APPEND)
	{
		((t_command*)item->content)->file_out = file;
		((t_command*)item->content)->redir = REDIR_OUT_APPEND;
	}
	parser->list = parser->list->next;
}

void			create_command(t_parsing *parser, t_list **command_list)
{
	int			arg_count;
	t_list		*item;
	int			i;

	arg_count = get_length(parser);
	item = make_item(arg_count);
	i = 0;
	while (parser->list &&
	check_seperator((char *)parser->list->content) == NO_SEP)
	{
		parser->redir = check_redir((char *)parser->list->content);
		if (parser->redir != NO_REDIR)
		{
			if (!parser->list->next)
			{
				parser->err = ERROR;
				return (error_syntax("newline"));
			}
			redir_handling(parser, item);
		}
		else
		{
			((t_command*)item->content)->args[i] = parser->list->content;
			i++;
		}
		parser->list = parser->list->next;
	}
	if (parser->cur_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_OUT;
	if (parser->prev_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_IN;
	if (parser->prev_sep == PIPE && parser->cur_sep == PIPE)
		((t_command*)item->content)->pipe = PIPE_BOTH;
	ft_lstadd_back(command_list, item);
}

t_list			*parse_line(t_list **list)
{
	t_parsing	parsing;
	t_list		*command_list;

	command_list = NULL;
	parsing.list = *list;
	parsing.prev_sep = NO_SEP;
	parsing.err = NO_ERROR;
	while ((*list) && ft_strcmp((*list)->content, ";"))
	{
		parsing.cur_sep = check_seperator((*list)->content);
		if (parsing.cur_sep != NO_SEP)
		{
			create_command(&parsing, &command_list);
			if (parsing.err == ERROR)
				return (NULL);
			parsing.prev_sep = parsing.cur_sep;
			parsing.list = (*list)->next;
		}
		(*list) = (*list)->next;
	}
	if (parsing.list)
		create_command(&parsing, &command_list);
	if (*list)
		(*list) = (*list)->next;
	return (command_list);
}
