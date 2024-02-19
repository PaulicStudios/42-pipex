/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/19 16:10:21 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_close(t_args *args)
{
	int ind;

	if (args->fd_in != -1)
		close(args->fd_in);
	if (args->fd_out != -1)
		close(args->fd_out);
	ft_close_pipes(args);
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
}

void	ft_exit_error(t_args *args, char *msg)
{
	ft_free_close(args);
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
	ft_execute_processes(&args, envp);
	ft_free_close(&args);
	ft_wait_for_processes();
	// sleep(999999);
}
