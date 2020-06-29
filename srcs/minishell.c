/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 13:16:03 by rpet          #+#    #+#                 */
/*   Updated: 2020/06/29 11:09:32 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		i;
	char	**tmp;
	char	**tmp2;

	tmp2 = malloc(sizeof(char *) * 3);
	(void)argc;
	(void)argv;
	tmp = env;
	while (*tmp)				//environment variables
	{
		printf("[%s]\n", *tmp);
		tmp++;
	}
	i = 1;
	tmp2[0] = "ls";
	tmp2[1] = ".";
	tmp2[2] = NULL;
	while (i)
	{
		ft_putstr_fd("minishell: ", 1);
		i = get_next_line(0, &line);
	/*	int id = fork();
		if (id != 0)
			wait(NULL);
		else
			execve("/bin/ls", tmp2, env);*/
		free(line);
	}
	return (0);
}
