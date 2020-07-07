/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 11:49:44 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/07/01 10:06:12 by rpet          ########   odam.nl         */
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

void	create_token(char *str)
{
	
}

void    ft_parse_line(char *line)
{
	int			quote;
	int			i;
	int			token_len;

	quote = 0; // 0 is geen 1 is single 2 is double
	i = 0;
    token_len = 0;
	if (line[i] == '\\')
		ft_error("Command not found");
	while (line[i] != '\0')
    {
		if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
		{
			if (line[i - 1] == '\\')

			}
			quote = 1;
		}
		i++;
    }
}

int		main(int argc, char **argv, char **env)
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
        ft_parse_line(line);
    }
	return (0);
}
