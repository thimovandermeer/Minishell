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
	if (!new_item)
		error_malloc();
	ft_lstadd_back(list, new_item);
}

void			redir_handling(t_parsing *parser, t_command *command,
								t_redirection redir)
{
	char		*file;
	t_filemode	*mode;
	t_list		*tmp;

	file = (char*)parser->list->next->content;
	if (redir == REDIR_IN)
		add_list(&(command->file_in), file);
	else
	{
		mode = malloc(sizeof(t_filemode));
		if (!mode)
			error_malloc();
		*mode = (redir == REDIR_OUT_APPEND) ? APPEND : TRUNC;
		add_list(&(command->file_out), file);
		add_list(&(command->out_mode), mode);
	}
	tmp = parser->list;
	parser->list = parser->list->next;
	free(tmp->content);
	free(tmp);
}

void			parse_pipes(t_command *command, t_parsing *parser)
{
	if (parser->cur_sep == PIPE)
		command->pipe = PIPE_OUT;
	if (parser->prev_sep == PIPE)
		command->pipe = PIPE_IN;
	if (parser->prev_sep == PIPE && parser->cur_sep == PIPE)
		command->pipe = PIPE_BOTH;
}

void			parse_command(t_command *command, t_parsing *parser,
								t_vars *vars)
{
	int				i;
	t_redirection	redir;
	t_list			*tmp;

	i = 0;
	while (parser->list &&
	check_seperator((char *)parser->list->content) == NO_SEP)
	{
		redir = check_redir((char *)parser->list->content);
		if (redir != NO_REDIR)
			redir_handling(parser, command, redir);
		else
		{
			command->args[i] = parser->list->content;
			i++;
		}
		tmp = parser->list;
		parser->list = parser->list->next;
		free(tmp);
	}
	parse_pipes(command, parser);
}

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

t_list			*parse_line(t_list **list, t_vars *vars)
{
	t_parsing	parsing;
	t_list		*command_list;
	t_list		*tmp;

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
