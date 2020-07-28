/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/20 08:50:29 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/07/28 11:02:04 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int		main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	*vars1[2];
	char	*vars2[3];
	pipe(fd);
	vars1[0] = "ls";
	vars1[1] = NULL;
	vars2[0] = "cat";
	vars2[1] = "-e";
	vars2[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve("/bin/ls", vars1, envp);
	}
	wait(NULL);
	close(fd[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		execve("/bin/cat", vars2, envp);
	}
	wait(NULL);
	printf("Done.\n");
	return (0);
}
