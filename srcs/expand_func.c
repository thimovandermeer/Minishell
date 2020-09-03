/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_func.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:49:40 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/09/03 18:19:32 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

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

void		expand_func(t_list *list, t_vars *vars)
{
	char		*token;
	char		*new;
	t_quote		quote;

	quote = NO_QUOTE;
	while (list && ft_strcmp(list->content, ";"))
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
		else
			list->content = ft_strdup(token);
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

	length = get_length_var_name(replace);
	printf("length = %i\n", length);
	if (quote == SINGLE_QUOTE)
		return (replace);
	length_start_str = ft_strlen(replace) - length;
	var_name = ft_substr(ft_strrchr(replace, '$'), 1, length);
	var_replace_value = search_var_name(var_name, vars->get_env);
	return (create_new_token(replace, var_replace_value, length_start_str));
}

char		*create_new_token(char *str1, char *str2, int len)
{
	char	*dst;
	char	*result;

	dst = ft_substr(str1, 0, len);
	if (dst && str2)
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
