/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:35:57 by rpet          #+#    #+#                 */
/*   Updated: 2020/01/10 10:04:09 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/*
**	When line is too long (aka characters after \n) it will be cut here.
*/

static char	*cut_line(char **line)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (strlen_gnl(*line) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while ((*line)[i] != '\0' && (*line)[i] != '\n')
	{
		str[i] = (*line)[i];
		i++;
	}
	str[i] = '\0';
	free(*line);
	return (str);
}

/*
**	Returns value 0 (EOF) or 1 (a line has been read) when everything goes well.
**	In case of an error everything will be freed and returns -1.
*/

static int	ret_value(char **line, char **str, int fd, int error)
{
	int		i;

	i = 0;
	if (strchr_gnl(*line) != -1 && error != -1)
		*line = cut_line(line);
	if (*line == NULL)
		error = -1;
	if (error == -1)
	{
		free(str[fd]);
		return (-1);
	}
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		strcpy_gnl(str[fd], str[fd] + i + 1, 0);
		return (1);
	}
	free(str[fd]);
	str[fd] = NULL;
	return (0);
}

/*
**	Starting function. Creates line.
*/

int			get_next_line(int fd, char **line)
{
	static char	*str[OPEN_MAX];
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (str[fd] == NULL)
	{
		str[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (str[fd] == NULL)
			return (-1);
		str[fd][0] = '\0';
	}
	*line = strdup_gnl(str[fd]);
	if (*line == NULL)
		return (ret_value(line, str, fd, -1));
	ret = 1;
	while (ret > 0 && strchr_gnl(str[fd]) == -1)
	{
		ret = read(fd, str[fd], BUFFER_SIZE);
		str[fd][ret] = '\0';
		*line = strjoin_gnl(*line, str[fd]);
		if (*line == NULL)
			return (ret_value(line, str, fd, -1));
	}
	return (ret_value(line, str, fd, 0));
}
