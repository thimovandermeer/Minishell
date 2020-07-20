/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/07/20 13:19:11 by rpet          ########   odam.nl         */
=======
/*   Updated: 2020/07/16 15:26:41 by thimovander   ########   odam.nl         */
>>>>>>> 411ade586232a20e9ae6b2e273b492071af55b8a
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str)
{
	write(1, "\e[31mERROR\n", 13);
	write(1, "\e[33m", 5);
	write(1, str, ft_strlen(str) + 1);
	exit(1);
}

size_t 	ft_env_len(char **envv)
{
	int i;

	i = 0;
	while(envv[i])
		i++;
	return (i);
}

void	init_envv(char **envv)
{
	int i;

	
	get_envv = (char **)malloc(sizeof(char*) * (ft_env_len(envv)+ 1));
	i = 0;
	while (envv[i])
	{
		if (!(get_envv[i] = ft_strdup(envv[i])))
			ft_error("Something went wrong with environment var's"); // dit moet nog aangepast worden naar een goeie error message
		i++;
	}
}

int 	ft_executable(char *bin_path, struct stat f,char **tokens, char **env)
{
	pid_t p_id;

	(void)f;
	p_id = fork();
	printf("binpath = %s\n", bin_path);
	if (p_id == 0)
		return (execve(bin_path, tokens, env));
	else if (p_id < 0)
		ft_error("failed to create child process\n");
	wait(&p_id); // dit zorgt ervoor dat the main proces niet door gaat totdat the child proces klaar is
	// signal handling ???? hier zometeen nog naar kijken
	// wat zijn de return values van fork ? kan hier ook iets in fout gaan? zo ja hoe ga ik dit fixen?
	// inprincipe als ik geen error krijg op fork kan ik execve aanroepen
	return (0);
}

int  check_bins(char **tokens, char **env)
{
	char 			**tmp;
	char 			**path;
	char 			*bin_path;
	struct stat		f; // check https://man7.org/linux/man-pages/man2/stat.2.html voor uitleg
	int 			i;
	i = 0;
	//  int lstat(const char *pathname, struct stat *statbuf);
	while (get_envv[i] != '\0')
	{
		tmp = ft_split(get_envv[i], '=');
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			int j;
			j = 0;
			path = ft_split(tmp[1], ':');
			while (path[j])
			{
				path[j] = ft_strjoin(path[j], "/");
				bin_path = ft_strjoin(path[j], tokens[0]);
				if (lstat(bin_path, &f) == -1)
					free(bin_path);
				else
					return (ft_executable(bin_path, f, tokens, env)); // vervolgend executable opstarten he met fork en de hele tering zooi
				j++;
			}
		}
		i++;
	}
	return (-1);
}

int 	ft_occurence(char *line, char c)
{
	int i;
	int occ;

	i = 0;
	occ = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			occ++;
		i++;
	}
	return (occ);
}

void 	ft_free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
	arr = NULL;
}

int 	is_builtin(char **tokens)
{
	if(ft_strncmp(tokens[0], "echo", ft_strlen("echo")) == 0)
		return (echo_func(tokens[1])); // all deze funcites 1 laten returen als het goed gaat
	if(ft_strncmp(tokens[0], "ECHO", ft_strlen("echo")) == 0)
		return (echo_func(tokens[1]));
	if(ft_strncmp(tokens[0], "cd", ft_strlen("cd")) == 0)
		return (cd_func(tokens[1]));
	if(ft_strncmp(tokens[0], "pwd", ft_strlen("pwd")) == 0)
		return(pwd_func(tokens[1]));
	if(ft_strncmp(tokens[0], "export", ft_strlen("export")) == 0)
		return(export_func(tokens[1]));
	if(ft_strncmp(tokens[0], "unset", ft_strlen("unset")) == 0)
		return(unset_func(tokens[1]));
	if(ft_strncmp(tokens[0], "env", ft_strlen("env")) == 0)
		return(env_func(tokens[1]));
	if(ft_strncmp(tokens[0], "exit", ft_strlen("exit")) == 0)
		return(exit_func(tokens[1]));

	return (0);


}

void 	parse_line(t_list *list, char **env)
{
	int		i;
	char	*line = NULL;

	(void) list;
	command = (char **)malloc(sizeof(char*) * ft_occurence(line, ';') + 1);
	if (!command)
		ft_error("malloc error\n");
	command = ft_split(line, ';');
	i = 0;
	// vanaf hier moet het blijven staan zoals het staat dus die commands moeten de structuur zijn en die tokens[0] moeten daaronder gehakt worden.
	while(command[i])
	{
		tokens = (char **)malloc(sizeof(char*) * ft_occurence(line, ' ') + 1);
		if (!tokens)
			ft_error("malloc error\n");
		tokens = ft_split(command[i], ' ');
		if (is_builtin(tokens) == 0 && check_bins(tokens, env) == -1)
			ft_error("Some sort of error message\n"); // deze nog even goed maken 
		ft_free_array(tokens);
		i++;
	}
}

// Lexer \/

void    print_list(t_list *list)
{
<<<<<<< HEAD
    int        i;

    i = 1;
    while (list)
    {
        printf("Token%i: [%s]\n", i, list->content);
        list = list->next;
        i++;
    }
}

void    str_error(char *str)
{
    write(1, "\e[31mERROR\n", 13);
    write(1, "\e[33m", 5);
    write(1, str, ft_strlen(str) + 1);
    exit(1);
}

void    found_double_quote(char *line, t_lexer *lexer)
{
    if (lexer->quote == DOUBLE_QUOTE)
        lexer->quote = NO_QUOTE;
    else
    {
        lexer->quote = DOUBLE_QUOTE;
        if (lexer->token == NOT_ACTIVE)
        {
            lexer->token = ACTIVE;
            lexer->token_len = 0;
            lexer->token_str = line;
        }
    }
}

void    found_single_quote(char *line, t_lexer *lexer)
{
    if (lexer->quote == SINGLE_QUOTE)
        lexer->quote = NO_QUOTE;
    else
    {
        lexer->quote = SINGLE_QUOTE;
        if (lexer->token == NOT_ACTIVE)
        {
            lexer->token = ACTIVE;
            lexer->token_len = 0;
            lexer->token_str = line;
        }
    }
}

int			check_metachar(char *line)
{
    char    meta_str[5];
    int        i;

    if (*line == '>' && *line + 1 == '>')
        return (1);
    ft_strlcpy(meta_str, ";|><", 5);
    i = 0;
    while (meta_str[i])
    {
        if (*line == meta_str[i])
            return (1);
        i++;
    }
    return (0);
}

/*
**    Adds a token to the list.
*/

int			create_token_for_list(t_lexer *lexer, t_list **list)
{
    t_list        *tmp;

    tmp = ft_lstnew(ft_substr(lexer->token_str, 0, lexer->token_len));
    if (!tmp)
        return (0);
    ft_lstadd_back(list, tmp);
    return (1);
}

/*
**    While not in a token, checks if it should start a new token.
*/

void		check_new_token1(char *line, t_lexer *lexer)
{
    if (check_metachar(line))
    {
        lexer->token = METACHAR;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
    else if (*line != ' ' && *line != '\t')
    {
        lexer->token = ACTIVE;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
}

/*
**    While in a token, checks if it should start a new token.
*/

int			check_new_token2(char *line, t_lexer *lexer, t_list **list)
{
    if (check_metachar(line))
    {
        if (!create_token_for_list(lexer, list))
            return (0);
        lexer->token = METACHAR;
        lexer->token_len = 0;
        lexer->token_str = line;
    }
    else if (*line == ' ' || *line == '\t')
    {
        if (!create_token_for_list(lexer, list))
            return (0);
        lexer->token = NOT_ACTIVE;
    }
    return (1);
}

/*
**    Checks where to split for tokens.
*/

char		*lexer_loop(char *line, t_lexer *lexer, t_list **list)
{
	if (*line == '\'' && lexer->quote != DOUBLE_QUOTE)
		found_single_quote(line, lexer);
	if (*line == '\"' && lexer->quote != SINGLE_QUOTE)
		found_double_quote(line, lexer);
	if (lexer->token == NOT_ACTIVE)
		check_new_token1(line, lexer);
	else if (lexer->token == ACTIVE && lexer->quote == NO_QUOTE)
	{
		if (!check_new_token2(line, lexer, list))
			return (NULL);
	}
	else if (lexer->token == METACHAR && lexer->quote == NO_QUOTE)
	{
		if (!create_token_for_list(lexer, list))
			return (NULL);
		lexer->token = NOT_ACTIVE;
	}
	if (lexer->token != NOT_ACTIVE)
		lexer->token_len++;
	return (line + 1);
}

/*
**    Calls the loop for the lexer.
*/

t_list		*lexer_line(char *line)
{
    t_lexer		lexer;
	t_list		*list;

	lexer.quote = NO_QUOTE;
	lexer.token = NOT_ACTIVE;
	lexer.token_len = 0;
	lexer.token_str = NULL;
	list = NULL;
	while (*line)
	{
		line = lexer_loop(line, &lexer, &list);
		if (!line)
			return (NULL);
		if (*line == '\0')
		{
			if (!create_token_for_list(&lexer, &list))
				return (NULL);
		}
	}
	return (list);
}

int			main(int argc, char **argv, char **env)
{
	int     	i;
	char    	*line;
	t_list		*list;

	i = 1;
	init_envv(argc, argv, env);
    while (i)
    {
		//command_prompt();
        i = get_next_line(0, &line);
        if (i == -1)
            ft_error("Something went wrong reading the line\n");
		list = lexer_line(line);
		if (list == NULL)
			str_error("Something went wrong during the lexer\n");
		print_list(list);
		//parse_line(list, env);
=======
    char    	*line;
	int 		ret;
	(void)		argc;
	(void)		argv;
	init_envv(env);
    while (1)
    {
		command_prompt();
        ret = get_next_line(0, &line);
        if (ret == -1)
            ft_error("Something went wrong reading the line\n");
		ft_parse_line_new(line, env);
>>>>>>> 411ade586232a20e9ae6b2e273b492071af55b8a
	}
	return (0);
}
