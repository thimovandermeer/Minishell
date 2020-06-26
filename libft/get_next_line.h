/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 15:11:18 by rpet          #+#    #+#                 */
/*   Updated: 2020/01/10 09:26:01 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);
int		strchr_gnl(char *str);
int		strlen_gnl(char *str);
char	*strdup_gnl(char *str);
void	strcpy_gnl(char *dst, char *src, int line);
char	*strjoin_gnl(char *s1, char *s2);

#endif
