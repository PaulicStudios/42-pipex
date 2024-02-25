/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:04:43 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 19:51:34 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"
# include "stdbool.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_process
{
	int		pipe_fd_in[2];
	int		pipe_fd_out[2];
	char	*cmd;
	char	**args;
	int		pid;
}			t_process;
typedef struct s_args
{
	char		*limiter;
	int			fd_in;
	int			fd_out;
	int			process_len;
	t_process	**processes;
}				t_args;

//pipex.c
void	ft_exit_error(t_args *args, char *msg);

//parse.c
t_args	ft_parse_args(int argc, char **argv, char **envp);

//here_doc.c
void	ft_handle_here_doc(t_args *args, char **argv, int argc);

//execute_process.c
void	ft_execute_processes(t_args *args, char **envp);
void	ft_wait_for_processes(void);
void	ft_free_close(t_args *args);

//fork.c
bool	ft_execute_process(t_process *process, char **envp);

//utils.c
void	ft_close_fd(int *fd);
void	ft_close_pipes(t_args *args);
void	ft_check_fd(int fd, t_args *args);
void	ft_wait_for_processes(void);

#endif
