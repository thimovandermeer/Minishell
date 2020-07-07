/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/07/07 12:01:15 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

void	ft_error(char *str)
{
	write(1, "\e[31mERROR\n", 13);
	write(1, "\e[33m", 5);
	write(1, str, ft_strlen(str) + 1);
	exit(1);
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
        if (*line == '\'')
		{
			line++;
            while(*line != '\'')
			{
				i++;
				line++;
			}
			quot_token = ft_substr(line - i, 0, i + 1);
		}
        if (*line == '\"')
		{
			line++;
			while(*line != '\"')
			{
				if (*line == '\\')
				{	
					line += 2;
					i += 2;
				}
				i++;
				line++;
			}
			quot_token = ft_substr(line - i, 0, i + 1);
			printf("Quot = %s\n", quot_token);
		}
		if (ft_st("NSEAW", *line))
			ft_split_chars();
		line++;
    }
}

int		main(int argc, char **argv, char **env)
{
    int     i;
    char    *line;

    i = 1;
	(void) argc;
	(void) argv;
	(void) env;
    while (i)
    {
        i = get_next_line(0, &line);
        if (i == -1)
            ft_error("Something went wrong reading the line\n");
        ft_parse_line(line);
    }
	return (0);
}
