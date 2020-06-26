/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:19:52 by rpet          #+#    #+#                 */
/*   Updated: 2019/10/30 15:26:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*ret;

	i = 0;
	ret = (char*)haystack;
	if (needle[i] == '\0')
		return (ret);
	while (haystack[i] != '\0' && len > 0)
	{
		j = 0;
		while (haystack[i] == needle[j] && len > j)
		{
			if (needle[j + 1] == '\0')
				return (ret + (i - j));
			i++;
			j++;
		}
		i = i - j;
		i++;
		len--;
	}
	return (NULL);
}
