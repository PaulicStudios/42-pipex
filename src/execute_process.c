/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:56:31 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/18 15:19:58 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_execute_process(t_process *process, int fd_read, int fd_write, char **envp)
{
	process->pid = fork();
	if (process->pid == -1)
		return false;
	if (process->pid == 0)
	{
		if (dup2(fd_read, STDIN_FILENO) == -10)
			return false;
		if (dup2(fd_write, STDOUT_FILENO) == -10)
			return false;
		close(fd_read);
		close(fd_write);
		execve(process->cmd, process->args, envp);
	}
	return true;
}

void	ft_wait_for_processes()
{
	int	status;
	int	pid;

	while ((pid = wait(&status)) > 0);
}

void	ft_execute_processes(t_args *args, char **envp)
{
	// int	std_in;
	// int	std_out;
	int	ind;
	t_process	*process;

	// std_in = dup2(args->fd_in, STDIN_FILENO);
	// std_out = dup2(args->fd_out, STDOUT_FILENO);
	ind = 0;
	while ((process = args->processes[ind]))
	{
		if (ind == 0)
		{
			if (pipe(process->pipe_fd) != 0)
				ft_exit_error(args, "Could not create pipe");
			ft_execute_process(process, args->fd_in, process->pipe_fd[PIPE_WRITE], envp);
		}
		if (ind == 1)
			ft_execute_process(process, args->processes[0]->pipe_fd[PIPE_READ], args->fd_out, envp);
		ind++;
	}
	close(args->processes[0]->pipe_fd[PIPE_READ]);
	close(args->processes[0]->pipe_fd[PIPE_WRITE]);
	close(args->fd_in);
	close(args->fd_out);
	ft_wait_for_processes();
}
