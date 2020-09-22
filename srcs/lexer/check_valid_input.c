/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_valid_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 13:14:43 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/22 11:53:21 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		is_redirection(char	*token)
{
	if (*token == '>' && *token + 1 == '>')
		return (1);
	if (*token == '>' || *token == '<')
		return (1);
	return (0);
}

/*int		syntax_redirection(t_list *list, t_vars *vars)
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
		}
		list = list->next;
	}
	return (1);
}*/

int		syntax_redirection(t_list *list, t_vars *vars)
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
		}
		list = list->next;
	}
	return (1);
}

int		syntax_multi_commands(t_list *list, t_vars *vars)
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

int		check_valid_input(t_list *list, t_vars *vars)
{
	if (!list)
		return (0);
	if (!syntax_multi_commands(list, vars))
		return (0);
	if (!syntax_redirection(list, vars))
		return (0);
	return (1);
}
