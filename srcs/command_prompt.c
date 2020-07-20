/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 10:59:33 by thimovander   #+#    #+#                 */
/*   Updated: 2020/07/16 13:29:38 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*get_env_var(char *str)
{
    char **tmp;
    char **path;
    char *home_path;
    struct stat		f;
    int i;

    i = 0;
	while(get_envv[i] != '\0')
	{
        printf("hier\n");
		tmp = ft_split(get_envv[i], '=');
		if (ft_strncmp(tmp[0], str, ft_strlen(tmp[0])) == 0)
		{
            printf("vindt hij een home ?\n");
			int j;
			j = 0;
			path = ft_split(tmp[1], ':');
			while(path[j])
			{
                printf("binnen path loop?\n");
				path[j] = ft_strjoin(path[j], "/");
                printf("doet mijn join het ?\n");
                printf("path = %s\n", path[j]);
                printf("tokens = %s\n", tokens[0]);
				home_path = ft_strjoin(path[j], tokens[0]);
                
				if (lstat(home_path, &f) == -1)
					free(home_path);
				else
					return (home_path);
				j++;
			}
		}
		i++;
	}
    return (NULL);
}

void    command_handler(int sig_num)
{
    if (sig_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        command_prompt();
        signal(SIGINT, command_handler);
    }
}

void    fork_handler(int sig_num)
{
    if (sig_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        signal(SIGINT, fork_handler);
    }
}
void 	command_prompt()
{
	char *cwd;
    char *home_cwd;
	char buff[4096 + 1];
    char *test;

    test = ft_strdup("~");
	cwd = getcwd(buff, 4096);
	home_cwd = ft_strjoin(test, cwd);
	ft_putstr_fd(home_cwd, 1);
    free(home_cwd);
    free(test);
	ft_putstr_fd("\033[32m--->\033[0m$", 1);
}
