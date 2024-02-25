/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:06:03 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 20:50:58 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fd(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void	ft_close_pipes(t_args *args)
{
	int	ind;

	if (!args->processes)
		return ;
	ind = 0;
	while (args->processes[ind])
	{
		ft_close_fd(&args->processes[ind]->pipe_fd_in[PIPE_READ]);
		ft_close_fd(&args->processes[ind]->pipe_fd_in[PIPE_WRITE]);
		ft_close_fd(&args->processes[ind]->pipe_fd_out[PIPE_READ]);
		ft_close_fd(&args->processes[ind]->pipe_fd_out[PIPE_WRITE]);
		ind++;
	}
}

void	ft_check_fd(int fd, t_args *args)
{
	if (fd == -1)
	{
		ft_free_close(args);
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

void	ft_wait_for_processes(void)
{
	int	status;
	int	pid;

	pid = 1;
	while (pid > 0)
		pid = wait(&status);
}
