/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 09:22:07 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/13 10:34:48 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*res;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	res = (unsigned char*)ptr;
	ft_bzero(res, (count * size));
	return (ptr);
}
