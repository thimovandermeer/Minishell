/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 09:19:48 by rpet          #+#    #+#                 */
/*   Updated: 2020/08/04 13:46:36 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	found_double_quote(char *line, t_lexer *lexer)
{
	if (lexer->quote == DOUBLE_QUOTE)
		lexer->quote = NO_QUOTE;
    else
    {
        lexer->quote = DOUBLE_QUOTE;
        if (lexer->token == NOT_ACTIVE)
        {
            lexer->token = ACTIVE;
            lexer->token_len = 0;
            lexer->token_str = line;
        }
    }
}

void    found_single_quote(char *line, t_lexer *lexer)
{
    if (lexer->quote == SINGLE_QUOTE)
        lexer->quote = NO_QUOTE;
    else
    {
        lexer->quote = SINGLE_QUOTE;
        if (lexer->token == NOT_ACTIVE)
        {
            lexer->token = ACTIVE;
            lexer->token_len = 0;
            lexer->token_str = line;
        }
    }
}

int            check_metachar(char *line)
{
    if (*line == '>' && *line + 1 == '>')
        return (1);
	if (ft_strchr(";|><", *line))
		return (1);
    return (0);
}

/*
**    Adds a token to the list.
*/

int            add_token_to_list(t_lexer *lexer, t_list **list)
{
	char	*token;
    t_list	*element;

	token = ft_substr(lexer->token_str, 0, lexer->token_len);
	if (!token)
		return (0);
	element = ft_lstnew(token);
	if (!element)
	{
		free(token);
		return (0);
	}
	ft_lstadd_back(list, element);
    return (1);
}

/*
**    While not in a token, checks if it should start a new token.
*/

void		outside_token(char *line, t_lexer *lexer)
{
    if (check_metachar(line))
    {
        lexer->token = METACHAR;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
    else if (*line != ' ' && *line != '\t')
    {
        lexer->token = ACTIVE;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
}

/*
**    While in a token, checks if it should start a new token.
*/

int			in_active_token(char *line, t_lexer *lexer, t_list **list)
{
    if (check_metachar(line))
    {
        if (!add_token_to_list(lexer, list))
            return (0);
        lexer->token = METACHAR;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
    else if (*line == ' ' || *line == '\t')
    {
        if (!add_token_to_list(lexer, list))
            return (0);
        lexer->token = NOT_ACTIVE;
    }
    return (1);
}

int			in_metachar_token(char *line, t_lexer* lexer, t_list **list)
{
	if (!add_token_to_list(lexer, list))
		return (0);
	if (*line == ' ' || *line == '\t')
		lexer->token = NOT_ACTIVE;
	else
	{
		lexer->token_str = line;
		lexer->token_len = 0;
		if (!check_metachar(line))
			lexer->token = ACTIVE;
	}
	return (1);
}

/*
**    Checks where to split for tokens.
*/

int			lexer_loop(char *line, t_lexer *lexer, t_list **list)
{
    if (*line == '\'' && lexer->quote != DOUBLE_QUOTE)
        found_single_quote(line, lexer);
    if (*line == '\"' && lexer->quote != SINGLE_QUOTE)
        found_double_quote(line, lexer);
	if (lexer->token == NOT_ACTIVE)
        outside_token(line, lexer);
	else if (lexer->token == ACTIVE && lexer->quote == NO_QUOTE)
    {
        if (!in_active_token(line, lexer, list))
            return (0);
    }
	else if (lexer->token == METACHAR && lexer->quote == NO_QUOTE)
    {
		if (!in_metachar_token(line, lexer, list))
			return (0);
    }
    if (lexer->token != NOT_ACTIVE)
        lexer->token_len++;
    return (1);
}

void		init_lexer(t_lexer *lexer)
{
	lexer->quote = NO_QUOTE;
	lexer->token = NOT_ACTIVE;
	lexer->token_len = 0;
	lexer->token_str = NULL;
}

/*
**    Calls the loop for the lexer.
*/

t_list		*lexer_line(char *line)
{
	t_lexer		lexer;
	t_list		*list;

	init_lexer(&lexer);
	list = NULL;
	while (*line)
	{
		if (!lexer_loop(line, &lexer, &list))
			return (NULL);
		line++;
	}
	if (!add_token_to_list(&lexer, &list))
		return (NULL);
	return (list);
}
