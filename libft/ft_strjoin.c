/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 16:23:12 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/07 09:15:42 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1i;
	size_t		s2i;
	char		*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1i = ft_strlen(s1);
	s2i = ft_strlen(s2);
	result = (char*)malloc(sizeof(char) * ((s1i + s2i) + 1));
	if (result == NULL)
		return (NULL);
	result[s1i + s2i] = '\0';
	while (s2i > 0)
	{
		result[s1i + s2i - 1] = s2[s2i - 1];
		s2i--;
	}
	while (s1i > 0)
	{
		result[s1i - 1] = s1[s1i - 1];
		s1i--;
	}
	return (result);
}
