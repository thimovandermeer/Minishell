/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_pos.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 11:21:43 by thimovander   #+#    #+#                 */
/*   Updated: 2020/10/02 13:51:25 by rpet          ########   odam.nl         */
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
