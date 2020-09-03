/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_valid_meta.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 13:14:43 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/02 14:17:52 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		check_valid_meta(t_list *list)
{
	int		len;

	while (list)
	{
		if (check_metachar(list->content))
		{
			len = ft_strlen(list->content);
			if (len > 2)
			{
				error_syntax(list->content + 2);
				return (0);
			}
			if (!ft_strcmp(list->content, "<") && list->next)
				if (!ft_strcmp(list->next->content, "<"))
				{
					error_syntax("<");
					return (0);
				}
		}
		list = list->next;
	}
	return (1);
}
