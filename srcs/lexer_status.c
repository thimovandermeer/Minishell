/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_status.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 11:06:14 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/02 11:05:43 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
**		Sets the token status to double quote or not active.
*/

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

/*
**		Sets the token status to single quote or not active.
*/

void	found_single_quote(char *line, t_lexer *lexer)
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

/*
**		While not in a token, checks if it should start a new token.
*/

void	outside_token(char *line, t_lexer *lexer)
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
**		While in a token, checks if it should start a new token.
*/

void	in_active_token(char *line, t_lexer *lexer, t_list **list)
{
	if (check_metachar(line))
	{
		add_token_to_list(lexer, list);
		lexer->token = METACHAR;
		lexer->token_len = 0;
		lexer->token_str = line;
	}
	else if (*line == ' ' || *line == '\t')
	{
		add_token_to_list(lexer, list);
		lexer->token = NOT_ACTIVE;
	}
}

void	in_metachar_token(char *line, t_lexer *lexer, t_list **list)
{
	if (*line == '>')
		return ;
	add_token_to_list(lexer, list);
	if (*line == ' ' || *line == '\t')
		lexer->token = NOT_ACTIVE;
	else
	{
		lexer->token_str = line;
		lexer->token_len = 0;
		if (!check_metachar(line))
			lexer->token = ACTIVE;
	}
}
