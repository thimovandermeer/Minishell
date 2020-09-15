/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:03:00 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/03 09:06:22 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

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

void	free_int_array(int **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void 	ft_free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void    print_list(t_list *list)
{
    int			i;
	int			len;

    i = 1;
    while (list)
    {
		len = ft_strlen(list->content);
		printf("Token %i: [%s] token_len: [%i]\n", i, list->content, len);
        list = list->next;
        i++;
    }
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

char	*get_env(char **env, char *key)
{
	int		i;
	int		key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
