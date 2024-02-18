/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/18 13:34:44 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit_error(t_args *args, char *msg)
{
	int	ind;

	if (args->fd_in != -1)
		close(args->fd_in);
	if (args->fd_out != -1)
		close(args->fd_out);
	if (args->processes)
	{
		ind = 0;
		while (args->processes[ind])
		{
			free(args->processes[ind]->cmd);
			ft_free_array((void **) args->processes[ind]->args);
			ind++;
		}
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 .. file2\n", 2);
		exit(1);
	}
	args = ft_parse_args(argc, argv, envp);
	int ind = 0;
	while (args.processes[ind])
	{
		printf("cmd: %s\n", args.processes[ind]->cmd);
		ind++;
	}

	// int fds[2];
	// pipe(fds);
	// dup2(args.fd_in, STDIN_FILENO);
	// dup2(args.fd_out, STDOUT_FILENO);

	// execve(args.processes[0]->cmd, args.processes[0]->args, envp);

	ft_execute_processes(&args, envp);

	// printf("fd_in: %d\n", args.fd_in);
	// printf("fd_out: %d\n", args.fd_out);
	// printf("cmd1: %s\n", args.cmds[0]);
	// printf("cmd2: %s\n", args.cmds[1]);
	// free(args.cmds);
}
