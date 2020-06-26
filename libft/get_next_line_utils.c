/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:40:25 by rpet          #+#    #+#                 */
/*   Updated: 2020/02/11 16:59:16 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		strchr_gnl(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[0] == '\n')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

char	*strdup_gnl(char *str)
{
	char	*ret;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	strcpy_gnl(char *dst, char *src, int line)
{
	int		i;
	int		new_line;

	i = 0;
	new_line = (line == 1) ? '\n' : '\0';
	while (src[i] != '\0' && src[i] != new_line)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = strlen_gnl(s1);
	len2 = strlen_gnl(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		free(s1);
		return (NULL);
	}
	result[len1 + len2] = '\0';
	strcpy_gnl(result, s1, 1);
	strcpy_gnl(result + len1, s2, 1);
	free(s1);
	return (result);
}
