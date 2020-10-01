#include "minishell.h"

/*
**	this function searches for the escape char
*/

void	found_escape_char(char *line, t_lexer *lexer)
{
	if (lexer->escape == ESCAPE)
		lexer->escape = NO_ESCAPE;
	else if (lexer->escape == NO_ESCAPE)
	{
		lexer->escape = ESCAPE;
		if (lexer->token == NOT_ACTIVE)
		{
			lexer->token = ACTIVE;
			lexer->token_len = 0;
			lexer->token_str = line;
		}
	}
}
