/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:56:31 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/18 17:41:03 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_pipe(t_process *process)
{
	close(process->pipe_fd_in[0]);
	close(process->pipe_fd_in[1]);
	close(process->pipe_fd_out[0]);
	close(process->pipe_fd_out[1]);
}

bool	ft_execute_process(t_process *process, char **envp)
{
	process->pid = fork();
	if (process->pid == -1)
		return false;
	if (process->pid == 0)
	{
		if (dup2(process->pipe_fd_in[PIPE_READ], STDIN_FILENO) == -1)
			return false;
		if (dup2(process->pipe_fd_out[PIPE_WRITE], STDOUT_FILENO) == -1)
			return false;
		ft_close_pipe(process);
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

void	ft_close_pipes(t_args *args)
{
	int	ind;

	ind = 0;
	while (args->processes[ind])
		ft_close_pipe(args->processes[ind]);
}

void	ft_execute_processes(t_args *args, char **envp)
{
	// int	std_in;
	// int	std_out;
	int	ind;

	// std_in = dup2(args->fd_in, STDIN_FILENO);
	// std_out = dup2(args->fd_out, STDOUT_FILENO);
	ind = 0;
	while (args->processes[ind])
	{
		if (ind == 0)
		{
			if (pipe(args->processes[ind]->pipe_fd_in) != 0)
				ft_exit_error(args, "Could not create pipe");
			dup2(args->fd_in, args->processes[ind]->pipe_fd_in[PIPE_READ]);
			close(args->fd_in);
			if (pipe(args->processes[ind]->pipe_fd_out) != 0)
				ft_exit_error(args, "Could not create pipe");
			ft_execute_process(args->processes[ind], envp);
		}
		if (ind == 1)
		{
			args->processes[ind]->pipe_fd_in[0] = args->processes[ind - 1]->pipe_fd_out[0];
			args->processes[ind]->pipe_fd_in[1] = args->processes[ind - 1]->pipe_fd_out[1];
			if (pipe(args->processes[ind]->pipe_fd_out) != 0)
				ft_exit_error(args, "Could not create pipe");
			dup2(1, args->processes[ind]->pipe_fd_out[PIPE_READ]);
			close(args->fd_out);
			ft_execute_process(args->processes[ind], envp);
		}
		ind++;
	}
	ft_close_pipes(args);
	close(args->fd_in);
	close(args->fd_out);
	ft_wait_for_processes();
}

// void	ft_execute_processes(t_args *args, char **envp)
// {
// 	// int	std_in;
// 	// int	std_out;
// 	// int	ind;
// 	// t_process	*process;
// 	int	pipe_fd[2];

// 	// std_in = dup2(args->fd_in, STDIN_FILENO);
// 	// std_out = dup2(args->fd_out, STDOUT_FILENO);
// 	if (pipe(pipe_fd) != 0)
// 		ft_exit_error(args, "Could not create pipe");

// 	int	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
// 		close(pipe_fd[PIPE_WRITE]);
// 		close(pipe_fd[PIPE_READ]);
// 		dup2(args->fd_in, STDIN_FILENO);
// 		close(args->fd_in);
// 		execve(args->processes[0]->cmd, args->processes[0]->args, envp);
// 	}

// 	int pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
// 		close(pipe_fd[PIPE_READ]);
// 		close(pipe_fd[PIPE_WRITE]);
// 		dup2(args->fd_out, STDOUT_FILENO);
// 		close(args->fd_out);
// 		execve(args->processes[1]->cmd, args->processes[1]->args, envp);
// 	}

// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	ft_wait_for_processes();
// }
