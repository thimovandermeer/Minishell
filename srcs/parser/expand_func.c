/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_func.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:45:36 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/10/01 13:45:36 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/*
**	this function returns the length of the var name
*/

int			get_length_var_name(char *replace)
{
	int i;

	i = 1;
	if (!(ft_isalpha(replace[i]) || replace[i] == '_'))
	{
		i++;
		return (i);
	}
	while (replace[i] && (ft_isalnum(replace[i]) || replace[i] == '_'))
		i++;
	return (i);
}

/*
**	this function returns the exit status as an int
*/

char		*exit_status(t_vars *vars)
{
	return (ft_itoa(vars->ret));
}

/*
**	this function expands the input to the appropriate environment vars
*/

void		expand_func(t_list *list, t_vars *vars)
{
	char		*new;
	t_quote		quote;
	t_list		*tmp;

	while (list && ft_strcmp(list->content, ";"))
	{
		quote = check_quote_type(list);
	//	shell_expansion(list->content, vars);
		remove_quotes(list->content, vars);
		free(list->content);
		list->content = NULL;
		if (ft_strrchr(vars->token, '$'))
		{
			if (vars->token[1] == '?')
				new = exit_status(vars);
			else
				new = expand_var(vars->token, vars, quote);
			if (!new)
			{
				free(new);
				error_malloc();
			}
			list->content = new;
		}
		else
			list->content = vars->token;
		list = list->next;
		quote = NO_QUOTE;
	}
}

/*
**	this function gets the length of the var and
**	activates the function which searches for the var name
*/

char		*expand_var(char *replace, t_vars *vars, t_quote quote)
{
	int		length;
	int		length_start_str;
	char	*var_name;
	char	*value;

	length = get_length_var_name(ft_strrchr(replace, '$'));
	var_name = ft_substr(ft_strrchr(replace, '$'), 1, length - 1);
	if (quote == SINGLE_QUOTE)
		return (replace);
	length_start_str = ft_strlen(replace) - length;
	value = search_var_name(var_name, vars->env);
	free(var_name);
	return (create_new_token(replace, value, length_start_str));
}

/*
**	this function create the return token for the expansion
*/

char		*create_new_token(char *replace, char *value, int len)
{
	char	*dst;
	char	*result;
	char	*bash;

	bash = NULL;
	if (replace[1] == '0')
		bash = ft_strdup("bash");
	if (replace[1] == '_')
		bash = ft_strdup("_");
	dst = ft_substr(replace, 0, len);
	if (dst && !bash)
		result = ft_strdup(dst);
	if (value)
		result = ft_strdup(value);
	if (bash && dst)
		result = ft_strjoin(bash, dst);
	if (dst && value)
		result = ft_strjoin(dst, value);
	free(dst);
	free(value);
	free(bash);
	free(replace);
	return (result);
}
