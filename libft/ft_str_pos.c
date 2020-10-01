/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_pos.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 11:21:43 by thimovander   #+#    #+#                 */
/*   Updated: 2020/09/30 11:26:46 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_str_pos(char *search_place, char search_val)
{
	int i;

	i = 0;
	while (search_place)
	{
		if (search_place[i] == search_val)
			return (i);
		i++;
	}
	return (0);
}