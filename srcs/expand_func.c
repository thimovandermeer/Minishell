/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_func.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:49:40 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/06 11:24:12 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_length_var_name(char *replace)
{
	int i;

	i = 1;
	while (replace[i] == '_' || ft_isalpha(replace[i]))
		i++;
	return (i);
}

void		expand_func(t_list *list, t_vars *vars)
{
	char	*token;
	char	*new;
	t_quote	quote;

	quote = NO_QUOTE;
	while (list != NULL && ft_strcmp(list->content , ";"))
	{
		if (ft_strchr(list->content, '\"'))
			quote = DOUBLE_QUOTE;
		else if (ft_strchr(list->content, '\''))
			quote = SINGLE_QUOTE;
		token = ft_strtrim(list->content, "\' \"");
		if (ft_strrchr(token, '$'))
		{
			new = expand_var(token, vars, quote);
			list->content = new;
		}
		list = list->next;
		quote = NO_QUOTE;
	}
}

char		*expand_var(char *replace, t_vars *vars, t_quote quote)
{
	int		length;
	int		length_start_str;
	char	*var_name;
	char	*var_replace_value;

	if (replace[1] == '?')
		return (ft_itoa(vars->ret));
	length = get_length_var_name(replace);
	if (quote == SINGLE_QUOTE)
		return (replace);
	length_start_str = ft_strlen(replace) - length;
	var_name = ft_substr(ft_strrchr(replace, '$'), 1, length);
	var_replace_value = search_var_name(var_name, vars->get_envv);
	return (create_new_token(replace, var_replace_value, length_start_str));
}

char		*create_new_token(char *str1, char *str2, int len)
{
	char	*dst;
	char	*result;

	dst = ft_substr(str1, 0, len);
	if (dst != NULL && str2 != NULL)
		result = ft_strjoin(dst, str2);
	else
		result = ft_strdup(dst);
	return (result);
}

char		*search_var_name(char *search_val, char **search_place)
{
	int		i;
	char	**key_pair;
	char	*replace_value;
	int		len;

	i = 0;
	while (search_place[i])
	{
		key_pair = ft_split(search_place[i], '=');
		len = ft_strlen(key_pair[0]);
		if (!ft_strncmp(key_pair[0], search_val, len))
		{
			replace_value = ft_strdup(key_pair[1]);
			return (replace_value);
		}
		i++;
	}
	return (NULL);
}
