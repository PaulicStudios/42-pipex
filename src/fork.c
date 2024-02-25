/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:37:06 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 19:38:01 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_execute_process(t_process *process, char **envp)
{
	process->pid = fork();
	if (process->pid == -1)
		return (false);
	if (process->pid == 0)
	{
		if (dup2(process->pipe_fd_in[PIPE_READ], STDIN_FILENO) == -1)
			return (false);
		ft_close_fd(&process->pipe_fd_in[PIPE_READ]);
		ft_close_fd(&process->pipe_fd_in[PIPE_WRITE]);
		if (dup2(process->pipe_fd_out[PIPE_WRITE], STDOUT_FILENO) == -1)
			return (false);
		ft_close_fd(&process->pipe_fd_out[PIPE_READ]);
		ft_close_fd(&process->pipe_fd_out[PIPE_WRITE]);
		execve(process->cmd, process->args, envp);
	}
	return (true);
}
