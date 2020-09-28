#include "minishell.h"

/*void	outside_token(char *line, t_lexer *lexer)
{
	
}*/

void	found_escape_char(char *line, t_lexer *lexer)
{
	if (lexer->token == NOT_ACTIVE)
		lexer->token = ESCAPE_CHAR;
	else if (lexer->token == ESCAPE_CHAR)
	{
		lexer->token = ACTIVE;
		lexer->token_len = 0;
		lexer->token_str = line;
	}
	else if (lexer->token == ACTIVE)
	{
		if (lexer->escape == NO_ESCAPE)
			lexer->escape = ESCAPE;
		
	}
	else if (lexer->escape == NO_ESCAPE)
	{
		lexer->escape = ESCAPE;
/*		if (lexer->token == NOT_ACTIVE)
			outside_token(line, 
		{
			lexer->token = ACTIVE;
			lexer->token_len = 0;
			lexer->token_str = line;
		}*/
	}
}
