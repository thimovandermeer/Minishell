/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/07/16 10:59:59 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	**get_envv;
char 	**tokens;
char	**command;

void	ft_error(char *str)
{
	write(1, "\e[31mERROR\n", 13);
	write(1, "\e[33m", 5);
	write(1, str, ft_strlen(str) + 1);
	exit(1);
}

void 	ft_split_chars(char *line, int bool, int i)
{
	char *split_token;
	char *token;
	split_token = NULL;
	if (bool == 0)
	{
		printf("test\n");
		// if(*line == '>' && *line + 1 == '>')
		// 	split_token = ">>";
		// else
		// 	split_token[0] = *line;
		printf("split_token = %s\n", split_token);
		token = ft_substr(line, 0, i);
		printf("token = %s\n", token);
	}
}

void    ft_parse_line(char *line)
{
	int		quote;

	quote = 0; // 0 is geen 1 is single 2 is double
    while(*line != '\0')
    {
		int i;
		i = 1;
		char *quot_token;
        if (line[i] == '\'')
		{
			i++;
            while(line[i] != '\'')
				i++;
			quot_token = ft_substr(line - i, 0, i + 1);
		}
        if (line[i] == '\"')
		{
			i++;
			while(line[i] != '\"')
			{
				if (line[i] == '\\')
					i += 2;
				i++;
			}
			quot_token = ft_substr(line - i, 0, i + 1);
		}
		if (ft_strrchr(";|<>", line[i]))
			ft_split_chars(line, quote, i);
		i++;
    }
	
}

size_t 	ft_env_len(char **envv)
{
	int i;

	i = 0;
	while(envv[i])
		i++;
	return (i);
}

void	init_envv(int argc, char **argv, char **envv)
{
	int i;

	(void)argc;
	(void)argv;
	get_envv = (char **)malloc(sizeof(char*) * (ft_env_len(envv)+ 1));
	i = 0;
	while(envv[i])
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

	if (p_id == 0)
		return (execve(bin_path, tokens, env));
	else if (p_id < 0)
		ft_error("failed to create child process\n");
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
	while(get_envv[i] != '\0')
	{
		tmp = ft_split(get_envv[i], '=');
		if (ft_strncmp(tmp[0], "PATH", ft_strlen(tmp[0])) == 0)
		{
			int j;
			j = 0;
			path = ft_split(tmp[1], ':');
			while(path[j])
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
	while(line[i] != '\0')
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
	if(ft_strncmp(tokens[0], "echo", ft_strlen("echo")) == 0)
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

void 	ft_parse_line_new(char *line, char **env)
{
	int		i;
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

int		main(int argc, char **argv, char **env)
{
    int     	i;
    char    	*line;
	// t_tokens 	**list; // hier ben ik gebleven bij het maken van een linked list voor onze verschillende commands

    i = 1;
	init_envv(argc, argv, env);
    while (i)
    {
		command_prompt();
        i = get_next_line(0, &line);
        if (i == -1)
            ft_error("Something went wrong reading the line\n");
        // ft_parse_line(line);
		ft_parse_line_new(line, env);
	}
}
