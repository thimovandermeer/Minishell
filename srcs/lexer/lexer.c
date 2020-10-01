#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**		Looks for a metachar.
*/

int		check_metachar(t_lexer *lexer, char cur_char)
{
	if (ft_strchr(";|><", cur_char))
	{
		lexer->metachar = cur_char;
		return (1);
	}
	return (0);
}

/*
**		Adds a token to the list.
*/

void	add_token_to_list(t_lexer *lexer, t_list **list)
{
	char	*token;
	t_list	*element;

	token = ft_substr(lexer->token_str, 0, lexer->token_len);
	if (!token)
		error_malloc();
	element = ft_lstnew(token);
	if (!element)
		error_malloc();
	ft_lstadd_back(list, element);
}

/*
**		Checks where to split for tokens.
*/

void	lexer_loop(char *line, t_lexer *lexer, t_list **list)
{
	if (*line == '\\' && lexer->quote != SINGLE_QUOTE)
		found_escape_char(line, lexer);
	if (*line == '\'' && lexer->quote != DOUBLE_QUOTE)
		found_single_quote(line, lexer);
	if (*line == '\"' && lexer->quote != SINGLE_QUOTE)
		found_double_quote(line, lexer);
	if (lexer->token == NOT_ACTIVE)
		outside_token(line, lexer);
	else if (lexer->token == ACTIVE && lexer->quote == NO_QUOTE)
		in_active_token(line, lexer, list);
	else if (lexer->token == METACHAR && lexer->quote == NO_QUOTE)
		in_metachar_token(line, lexer, list);
	if (*line != '\\' && lexer->escape == ESCAPE)
		lexer->escape = NO_ESCAPE;
	if (lexer->token != NOT_ACTIVE)
		lexer->token_len++;
}

/*
**		Initializes the lexer.
*/

void	init_lexer(t_lexer *lexer)
{
	lexer->token_len = 0;
	lexer->token_str = NULL;
	lexer->tmp = NULL;
	lexer->metachar = 0;
	lexer->escape = NO_ESCAPE;
	lexer->quote = NO_QUOTE;
	lexer->token = NOT_ACTIVE;
}

/*
**		Calls the loop for the lexer.
*/

t_list	*lexer_line(char *line)
{
	t_lexer		lexer;
	t_list		*list;

	init_lexer(&lexer);
	list = NULL;
	while (*line)
	{
		lexer_loop(line, &lexer, &list);
		line++;
	}
	if (lexer.token != NOT_ACTIVE)
		add_token_to_list(&lexer, &list);
	if (lexer.quote != NO_QUOTE)
	{
		ft_putendl_fd("multi-line is not supported", 2);
		exit(1);
	}
	return (list);
}
