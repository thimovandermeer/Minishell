/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 09:12:30 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/12 18:13:27 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*element;
	t_list		*start;

	if (lst == NULL)
		return (NULL);
	start = ft_lstnew((*f)(lst->content));
	if (start == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		element = ft_lstnew((*f)(lst->content));
		if (element == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, element);
		lst = lst->next;
	}
	return (start);
}
