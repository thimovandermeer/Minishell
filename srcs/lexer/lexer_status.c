#include "minishell.h"
#include "libft.h"

/*
**		Sets the token status to double quote or not active.
*/

void	found_double_quote(char *line, t_lexer *lexer)
{
	if (lexer->escape == ESCAPE)
		return ;
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
	if (lexer->escape == ESCAPE)
		return ;
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
	if (check_metachar(lexer, *line))
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
	if (check_metachar(lexer, *line))
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

/*
**		While in a meta token, checks if it should start a new token.
*/

void	in_metachar_token(char *line, t_lexer *lexer, t_list **list)
{
	if (check_metachar(lexer, lexer->metachar))
		if (*line == '>' && lexer->metachar == '>')
			return ;
	add_token_to_list(lexer, list);
	if (*line == ' ' || *line == '\t')
		lexer->token = NOT_ACTIVE;
	else
	{
		lexer->token_str = line;
		lexer->token_len = 0;
		if (!check_metachar(lexer, *line))
			lexer->token = ACTIVE;
	}
}
