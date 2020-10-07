/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:06 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/06 15:00:22 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function checks if there are
**	redirections and what type of redirections it are
*/

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

/*
**	this function parses the pipes and sets the command struct accordingly
*/

void			parse_pipes(t_command *command, t_parsing *parser)
{
	if (parser->cur_sep == PIPE)
		command->pipe = PIPE_OUT;
	if (parser->prev_sep == PIPE)
		command->pipe = PIPE_IN;
	if (parser->prev_sep == PIPE && parser->cur_sep == PIPE)
		command->pipe = PIPE_BOTH;
}

/*
**	this function parses the commands and fills in all the variables
*/

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

/*
**	this function function is activated when no seperator
**	 is found and will create a command
*/

void			no_sep_found_parsing(t_parsing *parsing, t_list **command_list,
									t_list **list, t_vars *vars)
{
	create_command(parsing, command_list, vars);
	parsing->prev_sep = parsing->cur_sep;
	parsing->list = (*list)->next;
}

/*
**	this is the driver function of the parse part
*/

t_list			*parse_line(t_list **list, t_vars *vars)
{
	t_parsing	parsing;
	t_list		*command_list;
	t_list		*tmp;

	command_list = NULL;
	tmp = NULL;
	parsing.list = *list;
	parsing.prev_sep = NO_SEP;
	parsing.err = NO_ERROR;
	while ((*list) && ft_strcmp((*list)->content, ";"))
	{
		parsing.cur_sep = check_seperator((*list)->content);
		if (parsing.cur_sep == PIPE)
			tmp = *list;
		if (parsing.cur_sep != NO_SEP)
			no_sep_found_parsing(&parsing, &command_list, list, vars);
		(*list) = (*list)->next;
		free_pipe_parse_line(&tmp);
	}
	if (parsing.list)
		create_command(&parsing, &command_list, vars);
	if (*list)
		free_parse_line(list);
	return (command_list);
}
