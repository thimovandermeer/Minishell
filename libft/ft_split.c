/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 16:33:41 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/13 18:56:50 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_countstrings(char const *s, char c)
{
	int		i;
	int		amount;

	i = 0;
	amount = 0;
	if (s[i] == c)
		amount--;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i + 1] != '\0')
				i++;
			amount++;
		}
		i++;
	}
	if (s[i - 1] != c)
		amount++;
	return (amount);
}

static char		*ft_create_string(char const *s, char c)
{
	char	*string;
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	string = malloc(sizeof(char) * (i + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static int		ft_count_start_string(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static char		**ft_array(char **result, const char *s, int amount, char c)
{
	int		i;

	i = 0;
	while (amount > i)
	{
		result[i] = ft_create_string(s, c);
		if (result[i] == NULL)
		{
			while (i > 0)
			{
				i--;
				free(result[i]);
			}
			free(result);
			return (NULL);
		}
		while (s[0] != c && s[0] != '\0')
			s++;
		while (s[0] == c && s[0] != '\0')
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		amount;
	int		start;

	if (s == NULL)
		return (NULL);
	if (*s == 0)
		amount = 0;
	else
		amount = ft_countstrings(s, c);
	result = malloc(sizeof(char*) * (amount + 1));
	if (result == NULL)
		return (NULL);
	start = ft_count_start_string(s, c);
	result = ft_array(result, s + start, amount, c);
	return (result);
}
