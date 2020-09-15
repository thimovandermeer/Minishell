/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_valid_meta.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 13:14:43 by rpet          #+#    #+#                 */
/*   Updated: 2020/09/07 14:27:17 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		check_first_char(char *str, t_vars *vars)
{
	if (*str == ';' || *str == '|')
	{
		error_syntax(str, vars);
		return (1);
	}
	return (0);
}

int		check_valid_meta(t_list *list, t_vars *vars)
{
	int		len;

	if (check_first_char((char*)list->content, vars))
		return (0);
	while (list)
	{
		if (check_metachar(list->content))
		{
			len = ft_strlen(list->content);
			if (len > 2)
			{
				error_syntax(list->content + 2, vars);
				return (0);
			}
			if (!ft_strcmp(list->content, "<") && list->next)
				if (!ft_strcmp(list->next->content, "<"))
				{
					error_syntax("<", vars);
					return (0);
				}
		}
		list = list->next;
	}
	return (1);
}
