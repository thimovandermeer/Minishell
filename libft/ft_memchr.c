/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:51:40 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/13 11:17:51 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char*)s;
	i = 0;
	while (n > i)
	{
		if (mem[i] == (unsigned char)c)
			return (mem + i);
		i++;
	}
	return (NULL);
}
