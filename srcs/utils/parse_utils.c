/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:46:57 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 15:15:11 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function checks for seperators
*/

t_separator		check_seperator(char *str)
{
	if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (NO_SEP);
}

/*
**	this function checks if the current item is a redirection or not
*/

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

/*
**	this function returns the length of the current command
*/

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

/*
**	this function free's the list if the pipe has been detected
*/

void			free_pipe_parse_line(t_list **tmp)
{
	if ((*tmp) != NULL)
	{
		free((*tmp)->content);
		(*tmp)->content = NULL;
		free((*tmp));
		(*tmp) = NULL;
	}
}

/*
**	this function free's the list if there
**	are stil elements after running the entire list
*/

void			free_parse_line(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	if (!ft_strcmp((*list)->content, ";"))
	{
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
	(*list) = (*list)->next;
}
