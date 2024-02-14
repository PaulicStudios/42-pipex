/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/14 22:22:51 by pgrossma         ###   ########.fr       */
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
			if (args->processes[ind]->fd_in != -1)
				close(args->processes[ind]->fd_in);
			if (args->processes[ind]->fd_out != -1)
				close(args->processes[ind]->fd_out);
			ind++;
		}
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	args = ft_parse_args(argc, argv, envp);
	int ind = 0;
	while (args.processes[ind])
	{
		printf("cmd: %s\n", args.processes[ind]->cmd);
		ind++;
	}

	execve(args.processes[0]->cmd, args.processes[0]->args, envp);

	// printf("fd_in: %d\n", args.fd_in);
	// printf("fd_out: %d\n", args.fd_out);
	// printf("cmd1: %s\n", args.cmds[0]);
	// printf("cmd2: %s\n", args.cmds[1]);
	// free(args.cmds);
}
