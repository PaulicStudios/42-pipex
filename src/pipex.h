/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:04:43 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/14 22:11:16 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_process
{
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**args;
}			t_process;
typedef struct s_args
{
	int			fd_in;
	int			fd_out;
	t_process	**processes;
}				t_args;

//pipex.c
void	ft_exit_error(t_args *args, char *msg);

//parse.c
t_args	ft_parse_args(int argc, char **argv, char **envp);

#endif
