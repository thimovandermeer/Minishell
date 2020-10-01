#include "minishell.h"
#include "libft.h"

/*
**	function which determines if token is redirection
*/

int		is_redirection(char *token)
{
	if (*token == '>' && *token + 1 == '>')
		return (1);
	if (*token == '>' || *token == '<')
		return (1);
	return (0);
}

/*
**	this function is checking the redirection syntax for errors
*/

int		syntax_redirections(t_list *list, t_vars *vars)
{
	while (list)
	{
		if (is_redirection(list->content))
		{
			if (ft_strlen(list->content) > 2)
			{
				error_syntax(list->content + 2, vars);
				return (0);
			}
			if (!ft_strcmp(list->content, "<") && list->next)
				if (!ft_strcmp(list->next->content, "<"))
				{
					error_syntax("<", vars);
					return (0);
				}
			if (!list->next)
			{
				error_syntax("newline", vars);
				return (0);
			}
		}
		list = list->next;
	}
	return (1);
}

/*
**	this function is checking the seperator syntax for errors
*/

int		syntax_seperators(t_list *list, t_vars *vars)
{
	char	*cur;
	char	*next;

	if (!ft_strcmp(list->content, "|") || !ft_strcmp(list->content, ";"))
	{
		error_syntax(list->content, vars);
		return (0);
	}
	while (list && list->next)
	{
		cur = list->content;
		next = list->next->content;
		if (!next)
			return (1);
		if ((!ft_strcmp(cur, "|") || !ft_strcmp(cur, ";")) &&
			(!ft_strcmp(next, "|") || !ft_strcmp(next, ";")))
		{
			error_syntax(cur, vars);
			return (0);
		}
		list = list->next;
	}
	return (1);
}

/*
**	this function checks if the input is valid
*/

void	check_multi_line(t_list *list, t_vars *vars)
{
	while (list->next)
		list = list->next;
	if (!ft_strcmp(list->content, "|"))
	{
		error_general("multi-line is not supported", vars);
		exit(1);
	}
}

int		check_valid_input(t_list *list, t_vars *vars)
{
	if (!list)
		return (0);
	check_multi_line(list, vars);
	if (!syntax_seperators(list, vars))
		return (0);
	if (!syntax_redirections(list, vars))
		return (0);
	return (1);
}
