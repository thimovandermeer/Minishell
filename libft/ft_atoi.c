/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:59:58 by rpet          #+#    #+#                 */
/*   Updated: 2019/11/13 09:15:08 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				neg;

	i = 0;
	result = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' \
			|| str[i] == '\t' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (result >= 9223372036854775807 && neg == 1)
			return (-1);
		else if (result > 9223372036854775807 && neg == -1)
			return (0);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)(result * neg));
}
