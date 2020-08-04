/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/08/04 14:59:26 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	is_builtin(t_command *command)
{
	if (ft_strncmp(command->args[0], "echo", ft_strlen("echo")) == 0)
		command->ret = (echo_func(command)); // all deze funcites 0 laten returen als het goed gaat
	// if (ft_strncmp(command->args[0], "ECHO", ft_strlen("echo")) == 0)
	// 	command->ret = (echo_func(command));
	// if (ft_strncmp(command->args[0], "cd", ft_strlen("cd")) == 0)
	// 	command->ret = (cd_func(command));
	// if (ft_strncmp(command->args[0], "pwd", ft_strlen("pwd")) == 0)
	// 	command->ret = (pwd_func(command));
	// if (ft_strncmp(command->args[0], "export", ft_strlen("export")) == 0)
	// 	command->ret = (export_func(command));
	// if (ft_strncmp(command->args[0], "unset", ft_strlen("unset")) == 0)
	// 	command->ret = (unset_func(command));
	// if (ft_strncmp(command->args[0], "env", ft_strlen("env")) == 0)
	// 	command->ret = (env_func(command));
	// if (ft_strncmp(command->args[0], "exit", ft_strlen("exit")) == 0)
	// 	command->ret = (exit_func(command));
	return (0);
}

void		kill_control_c()
{
	
}

void 		kill_control_slash()
{
	
}

int			get_length_var_name(char *replace)
{
	int i;

	i = 1;
	while (replace[i] == '_' || ft_isalpha(replace[i]))
		i++;
	return (i);
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

char		*expand_var(char *replace, t_vars *vars, t_quote quote)
{
	int		length;
	int		length_start_str;
	char	*var_name;
	char	*var_replace_value;

	length = get_length_var_name(replace);
	printf("quote = %u\n", quote);
	if (quote == DOUBLE_QUOTE)
	{
		length_start_str = ft_strlen(replace) - length;
		var_name = ft_substr(ft_strrchr(replace, '$'), 1, length);
		var_replace_value = search_var_name(var_name, vars->get_envv);
		return (create_new_token(replace, var_replace_value, length_start_str));
	}
	else
		return (replace);
}

void	expand_func(t_list *list, t_vars *vars)
{
	char	*token;
	char	*new;
	t_quote	quote;

	quote = NO_QUOTE;
	while (list != NULL)
	{
		if (ft_strrchr(token, '\"'))
		{
			printf("kom ik hier?\n");
			quote = DOUBLE_QUOTE;
		}
		else if (ft_strchr(token, '\''))
		{
			printf("kom ik hier wel?\n");
			quote = SINGLE_QUOTE;
		}
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

int			main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_list		*list;
	t_list		*command_list;
	t_vars		vars;

	(void)argv;
	(void)argc;
	i = 1;
	init_envv(env, &vars);
	while (i)
	{
		command_prompt();
		// signal(SIGINT, kill_control_c); // deze zo afmaken
		// signal(SIGINT, kill_control_slash); // deze zo afmaken
		i = get_next_line(0, &line);
		if (i == -1)
			ft_error("Something went wrong reading the line\n");
		list = lexer_line(line);
		print_list(list);
		expand_func(list, &vars);
		print_list(list);
		if (list == NULL)
			str_error("Something went wrong during the lexer\n");
		command_list = parse_line(list);
		iterate_command(command_list, env, &vars);
	}
	return (0);
}
