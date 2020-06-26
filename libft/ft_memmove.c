/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:57:42 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/12 09:54:12 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	size_t				i;

	pdst = dst;
	psrc = src;
	i = 0;
	if (pdst == NULL && src == NULL)
		return (NULL);
	if (pdst > psrc && pdst < psrc + len)
	{
		while (len > 0)
		{
			len--;
			pdst[len] = psrc[len];
		}
	}
	while (len > i)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
