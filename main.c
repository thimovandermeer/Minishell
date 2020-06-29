/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/06/29 14:10:54 by thvan-de      ########   odam.nl         */
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

void 	ft_create_token()
{
	
	ft_lstadd_back()
}

void    ft_found_quot(char **line, int  quote)
{
	int i;

	i = 0;
	if (line[i] -1 == '\\' && quote ==  '0')
		ft_error("Multiline command not handled by our program\n");
	else if (line[i] -1 == '\\' && quote ==  '\"')
		
		
	while(line[i] != quote)
	{

	}
	ft_create_token()
}

void 	ft_new_command()
{

	ft_create_token()
}

void 	ft_check_redirect(line)
{
	
	ft_create_token()
}

void    ft_parse_line(char **line)
{
	char		quote;

	quote = '0'; // 0 is geen 1 is single 2 is double
    while(*line != '\0')
    {
        if (*line == '\"' && quote == '0')
		{
			quote = '\"';
            ft_found_quot(line, quote);
		}
        if (*line == '\'' && quote == '0')
		{
			quote = '\'';
            ft_found_quot(line, quote);
		}
		if (*line == ';')
			ft_new_command(line);
		ft_check_redirect(line);
    }
}

int main(int argc, char **argv, char **env)
{
    int     i;
    char    *line;
    int     fd;

    i = 1;

    while (i)
    {
        i = get_next_line(0, &line);
        if (i == -1)
            ft_error("Something went wrong reading the line\n");
        ft_parse_line(&line);
    }

}