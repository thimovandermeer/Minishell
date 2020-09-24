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

char		*exit_status(t_vars *vars)
{
	return (ft_itoa(vars->ret));
}

t_quote		check_quote_type(t_list *list)
{
	t_quote		quote;

	quote = NO_QUOTE;
	if (ft_strchr(list->content, '\"'))
		quote = DOUBLE_QUOTE;
	else if (ft_strchr(list->content, '\''))
		quote = SINGLE_QUOTE;
	return (quote);
}

void		expand_func(t_list *list, t_vars *vars)
{
	char		*token;
	char		*new;
	t_quote		quote;

	while (list && ft_strcmp(list->content , ";"))
	{
		quote = check_quote_type(list);
		token = ft_strtrim(list->content, "\' \"");
		if (!token)
			error_malloc();
		if (ft_strrchr(token, '$'))
		{
			if (token[1] == '?')
				new = exit_status(vars);
			else
				new = expand_var(token, vars, quote);
			if (!new)
				error_malloc();
			list->content = new;
		}
		else
			list->content = token;
		list = list->next;
		quote = NO_QUOTE;
	}
}

char		*expand_var(char *replace, t_vars *vars, t_quote quote)
{
	int		length;
	int		length_start_str;
	char	*var_name;
	char	*value;

	length = get_length_var_name(replace);
	var_name = ft_substr(replace, 1, length - 1);
	if (quote == SINGLE_QUOTE)
		return (replace);
	length_start_str = ft_strlen(replace) - length;
	value = search_var_name(var_name, vars->get_env);
	free(var_name);
	return (create_new_token(replace, value, length_start_str));
}

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
	dst = ft_substr(replace, 2, len);
	free(replace);
	if (dst && !bash)
		result = ft_strdup(dst);
	if (value)
		result = ft_strdup(value);
	if (bash && dst)
		result = ft_strjoin(bash, dst);
	free(dst);
	free(value);
	free(bash);
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
