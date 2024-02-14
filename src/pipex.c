/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/14 22:06:20 by pgrossma         ###   ########.fr       */
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
		// while (args->processes[ind].cmd)
		// {
		// 	free(args->processes[ind].cmd);
		// 	if (args->processes[ind].fd_in != -1)
		// 		close(args->processes[ind].fd_in);
		// 	if (args->processes[ind].fd_out != -1)
		// 		close(args->processes[ind].fd_out);
		// 	ind++;
		// }
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	args = ft_parse_args(argc, argv, envp);
	int ind = 0;
	while (args.processes[ind]->cmd)
	{
		printf("cmd: %s\n", args.processes[ind]->cmd);
		ind++;
	}

	// char	**cmd1 = ft_split(args.cmds[0], ' ');
	// execve(cmd1[0], cmd1, envp);

	// printf("fd_in: %d\n", args.fd_in);
	// printf("fd_out: %d\n", args.fd_out);
	// printf("cmd1: %s\n", args.cmds[0]);
	// printf("cmd2: %s\n", args.cmds[1]);
	// free(args.cmds);
}
