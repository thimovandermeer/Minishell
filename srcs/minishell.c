/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/07/23 12:00:41 by rpet          ########   odam.nl         */
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
	printf("allemaal biins heeee\n");
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
	if (ft_strncmp(tokens[0], "echo", ft_strlen("echo")) == 0)
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

void    print_commands(t_list *command_list)
{
	int		i;

	while (command_list)
	{
		i = 0;
		while (((t_command*)command_list->content)->args[i] != '\0')
		{
			printf("args: [%s]\n", ((t_command*)command_list->content)->args[i]);
			i++;
		}
		command_list = command_list->next;
	}
}

int		check_seperator(char *str)
{
	if (!ft_strcmp(str, ";"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	return (0);
}

t_list 	*parse_line(t_list *list) // return value aanpassen naar linkedlist
{
	int			arg_count;
	int 		j;
	t_list  	*command_list;
	t_command 	command;
	t_list 		*tmp;
	t_list		*head_command;

	command_list = NULL;
	head_command = list;
	// iterate totdat je een pipe of een puntkomma tegenkomt
	// seperater bouwen en ook redirections checken 
	// 
	while (list)
	{
		head_command = list;
		arg_count = 0;
		while (list && !check_seperator(list->content))
		{
			arg_count++;
			list = list->next;
		}
		command.args = (char**)malloc(sizeof(char *) * (arg_count + 1));
		if (!command.args)
			return (NULL);
		j = 0;
		while (j < arg_count)
		{
			command.args[j] = head_command->content;
			head_command = head_command->next;
			j++;
		}
		command.args[j] = NULL;
		command.pipe = 0; //is stierenschijt, moet nog worden gedaan.
		tmp = ft_lstnew(&command);
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&command_list, tmp);
		if (list)
			list = list->next;
	}
	return (command_list);
}

void iterate_command(t_list *command_list, char **env)
{

	// printf("command = %s\n", ((t_command*)command_list->content)->args[0]);
	// vanaf hier moet het blijven staan zoals het staat dus die commands moeten de structuur zijn en die tokens[0] moeten daaronder gehakt worden.
	while (command_list)
	{
		if (is_builtin(((t_command*)command_list->content)->args) == 0 && check_bins(((t_command*)command_list->content)->args, env) == -1)
			ft_error("Some sort of error message\n"); // deze nog even goed maken 
		command_list = command_list->next;
	}
}

void    print_list(t_list *list)
{
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

int			main(int argc, char **argv, char **env)
{
	int     	i;
	char    	*line;
	t_list		*list;
	t_list 		*command_list;

	(void)argv;
	(void)argc;
	i = 1;
	init_envv(env);
    while (i)
    {
		command_prompt();
        i = get_next_line(0, &line);
        if (i == -1)
            ft_error("Something went wrong reading the line\n");
		list = lexer_line(line);
		if (list == NULL)
			str_error("Something went wrong during the lexer\n");
		print_list(list);
		command_list = parse_line(list);
		//print_commands(command_list);
		//iterate_command(command_list, env);
	}
	return (0);
}
