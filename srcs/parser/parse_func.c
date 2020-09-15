/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:04:51 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/15 10:50:21 by thvan-de      ########   odam.nl         */
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

t_list			*make_item(int arg_count, t_vars *vars)
{
	t_command	*command;
	t_list		*tmp;

	command = malloc(sizeof(t_command));
	if (!command)
		error_malloc(vars);
	tmp = ft_lstnew(command);
	if (!tmp)
	{
		free(command);
		error_malloc(vars);
	}
	command->args = (char**)malloc(sizeof(char *) * (arg_count + 1));
	if (!command->args)
	{
		ft_free_array(command->args);
		error_malloc(vars);
	}
	command->args[arg_count] = NULL;
	command->pipe = NO_PIPE;
	command->redir = NO_REDIR;
	command->file_in = NULL;
	command->file_out = NULL;
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

void			add_list(t_list **list, void *content)
{
	t_list		*new_item;

	new_item = ft_lstnew(content);
	// if (new_item == NULL)
	// 	shell_error_malloc();
	ft_lstadd_back(list, new_item);
}

void			redir_handling(t_parsing *parser, t_command *command)
{
	char 		*file;
	t_filemode	*mode;
	t_list		*tmp;

	file = parser->list->next->content;
	if (parser->redir == REDIR_IN)
		add_list(&(command->file_in), file);
	else
	{
		mode = malloc(sizeof(t_filemode));
		// if (mode == NULL)
		// 	shell_error_malloc();
		printf("redir = %u\n", parser->redir);
		*mode = (parser->redir == REDIR_OUT_APPEND ? APPEND : TRUNC);
		printf("mode = %i\n", (int)mode);
		add_list(&(command->file_out), file);
		add_list(&(command->out_mode), mode);
	}
	tmp = parser->list;
	parser->list = parser->list->next;
	free(tmp->content);
	free(tmp);
}

void	print_command_info(t_command *command)
{
	int i;
	t_list *tmp_out;
	t_list *tmp_in;
	t_list *tmp_out_mode;

	tmp_in = command->file_in;
	tmp_out = command->file_out;
	tmp_out_mode = command->out_mode;
	i = 0;
	printf("-----command info-------\n");
	printf("command = %s\n", command->args[0]);
	printf("-----files in-----\n");
	while (tmp_in)
	{
		printf("file_in = %s\n", tmp_in->content);
		tmp_in = tmp_in->next;
	}
	printf("-----files out------\n");
	while (tmp_out)
	{
		printf("file_out = %s\n", tmp_out->content);
		tmp_out = tmp_out->next;
		tmp_out_mode = tmp_out_mode->next;
	}
}

void			create_command(t_parsing *parser, t_list **command_list, t_vars *vars)
{
	int			arg_count;
	t_list		*command;
	int			i;

	arg_count = get_length(parser);
	command = make_item(arg_count, vars);
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
				return (error_syntax("newline", vars));
			}
			redir_handling(parser, (t_command*)command->content);
		}
		else
		{
			((t_command*)command->content)->args[i] = parser->list->content;
			i++;
		}
		parser->list = parser->list->next;
	}
	print_command_info((t_command*)command->content);
	if (parser->cur_sep == PIPE)
		((t_command*)command->content)->pipe = PIPE_OUT;
	if (parser->prev_sep == PIPE)
		((t_command*)command->content)->pipe = PIPE_IN;
	if (parser->prev_sep == PIPE && parser->cur_sep == PIPE)
		((t_command*)command->content)->pipe = PIPE_BOTH;
	ft_lstadd_back(command_list, command);
}

t_list			*parse_line(t_list **list, t_vars *vars)
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
			create_command(&parsing, &command_list, vars);
			if (parsing.err == ERROR)
				return (NULL);
			parsing.prev_sep = parsing.cur_sep;
			parsing.list = (*list)->next;
		}
		(*list) = (*list)->next;
	}
	if (parsing.list)
		create_command(&parsing, &command_list, vars);
	if (*list)
		(*list) = (*list)->next;
	return (command_list);
}
