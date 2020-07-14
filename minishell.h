/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 07:33:20 by rpet          #+#    #+#                 */
/*   Updated: 2020/07/14 16:08:03 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

typedef	struct	s_tokens {
	char	*data;
	void	*next;

}				t_tokens;

int 	cd_func(char *token);
int 	echo_func(char *token);
int 	env_func(char *token);
int 	exit_func(char *token);
int 	export_func(char *token);
int 	pwd_func(char *token);
int 	unset_func(char *token);


#endif
