/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_pos.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 14:52:25 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/02 14:52:26 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_str_pos(char *search_place, char search_val)
{
	int i;

	i = 0;
	while (search_place[i])
	{
		if (search_place[i] == search_val)
			return (i);
		i++;
	}
	return (0);
}
