/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:56:31 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 19:37:53 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_one_process(int ind, t_args *args, char **envp)
{
	args->processes[ind]->pipe_fd_in[PIPE_READ] = args->fd_in;
	args->processes[ind]->pipe_fd_out[PIPE_WRITE] = args->fd_out;
	ft_execute_process(args->processes[ind], envp);
}

void	ft_init_first_process(int ind, t_args *args, char **envp)
{
	if (pipe(args->processes[ind]->pipe_fd_out) != 0)
		ft_exit_error(args, "Could not create pipe");
	args->processes[ind]->pipe_fd_in[PIPE_READ] = args->fd_in;
	ft_execute_process(args->processes[ind], envp);
}

void	ft_init_process(int ind, t_args *args, char **envp)
{
	if (pipe(args->processes[ind]->pipe_fd_out) != 0)
		ft_exit_error(args, "Could not create pipe");
	args->processes[ind]->pipe_fd_in[PIPE_READ]
		= args->processes[ind - 1]->pipe_fd_out[PIPE_READ];
	args->processes[ind]->pipe_fd_in[PIPE_WRITE]
		= args->processes[ind - 1]->pipe_fd_out[PIPE_WRITE];
	ft_execute_process(args->processes[ind], envp);
	ft_close_fd(&args->processes[ind]->pipe_fd_in[PIPE_READ]);
	ft_close_fd(&args->processes[ind]->pipe_fd_in[PIPE_WRITE]);
}

void	ft_init_last_process(int ind, t_args *args, char **envp)
{
	args->processes[ind]->pipe_fd_in[PIPE_READ]
		= args->processes[ind - 1]->pipe_fd_out[PIPE_READ];
	args->processes[ind]->pipe_fd_in[PIPE_WRITE]
		= args->processes[ind - 1]->pipe_fd_out[PIPE_WRITE];
	args->processes[ind]->pipe_fd_out[PIPE_WRITE] = args->fd_out;
	ft_execute_process(args->processes[ind], envp);
}

void	ft_execute_processes(t_args *args, char **envp)
{
	int	ind;

	ind = 0;
	while (args->processes[ind])
	{
		if (ind == 0 && ind == args->process_len - 1)
			ft_init_one_process(ind, args, envp);
		else if (ind == 0)
			ft_init_first_process(ind, args, envp);
		else if (ind == args->process_len - 1)
			ft_init_last_process(ind, args, envp);
		else
			ft_init_process(ind, args, envp);
		ind++;
	}
}
