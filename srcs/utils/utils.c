
#include "minishell.h"
#include "libft.h"
#include <unistd.h>

/*
**	function which checks where in a string a char occurs
*/

int		ft_occurence(char *line, char c)
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

/*
**	function which prints the entire list
*/

void	print_list(t_list *list)
{
	int			i;

	i = 1;
	while (list)
	{
		printf("Token %i: [%s] addr: [%p]\n", i, list->content, list->content);
		list = list->next;
		i++;
	}
}

/*
**	function which returns the environments
*/

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

/*
**	function which sets the environment
*/

char	**set_new_env(char **array, int length)
{
	int		i;
	char	**tmp_list;

	tmp_list = (char **)malloc(sizeof(char*) * (length + 1));
	i = 0;
	while (array[i])
	{
		tmp_list[i] = ft_strdup(array[i]);
		printf("tmp_list[%i] = %s\n", i, tmp_list[i]);
		i++;
	}
	return (tmp_list);
}

/*
**	function which sort a string array alphabatically
*/

char	**bubblesort(char **array, int length)
{
	int		i;
	int		j;
	char	**tmp_list;
	char	*tmp;

	tmp_list = set_new_env(array, length);
	i = 0;
	while (tmp_list[i])
	{
		j = i + 1;
		while (tmp_list[j])
		{
			if (ft_strcmp(tmp_list[i], tmp_list[j]) > 0)
			{
				tmp = tmp_list[i];
				tmp_list[i] = tmp_list[j];
				tmp_list[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tmp_list);
}
