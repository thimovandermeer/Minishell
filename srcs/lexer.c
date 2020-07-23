/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 09:19:48 by rpet          #+#    #+#                 */
/*   Updated: 2020/07/23 11:12:13 by rpet          ########   odam.nl         */
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

int            create_token_for_list(t_lexer *lexer, t_list **list)
{
    t_list        *tmp;

    tmp = ft_lstnew(ft_substr(lexer->token_str, 0, lexer->token_len));
    if (!tmp)
        return (0);
    ft_lstadd_back(list, tmp);
    return (1);
}

/*
**    While not in a token, checks if it should start a new token.
*/

void        check_new_token1(char *line, t_lexer *lexer)
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

int            check_new_token2(char *line, t_lexer *lexer, t_list **list)
{
    if (check_metachar(line))
    {
        if (!create_token_for_list(lexer, list))
            return (0);
        lexer->token = METACHAR;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
    else if (*line == ' ' || *line == '\t')
    {
        if (!create_token_for_list(lexer, list))
            return (0);
        lexer->token = NOT_ACTIVE;
    }
    return (1);
}

/*
**    Checks where to split for tokens.
*/

char        *lexer_loop(char *line, t_lexer *lexer, t_list **list)
{
	printf("line start: [%s]\n", line);
    if (*line == '\'' && lexer->quote != DOUBLE_QUOTE)
        found_single_quote(line, lexer);
    if (*line == '\"' && lexer->quote != SINGLE_QUOTE)
        found_double_quote(line, lexer);
    if (lexer->token == NOT_ACTIVE)
        check_new_token1(line, lexer);
    else if (lexer->token == ACTIVE && lexer->quote == NO_QUOTE)
    {
		printf("line active check: [%s]\n", line);
        if (!check_new_token2(line, lexer, list))
            return (NULL);
    }
    else if (lexer->token == METACHAR && lexer->quote == NO_QUOTE)
    {
		printf("line metachar check1: [%s]\n", line);
        if (!create_token_for_list(lexer, list))
            return (NULL);
        lexer->token = NOT_ACTIVE;
    }
    if (lexer->token != NOT_ACTIVE)
        lexer->token_len++;
    return (line + 1);
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

t_list        *lexer_line(char *line)
{
    t_lexer        lexer;
    t_list        *list;

	init_lexer(&lexer);
    list = NULL;
    while (*line)
    {
        line = lexer_loop(line, &lexer, &list);
        if (!line)
            return (NULL);
        if (*line == '\0')
        {
            if (!create_token_for_list(&lexer, &list))
                return (NULL);
        }
    }
    return (list);
}
