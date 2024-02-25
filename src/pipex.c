/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 20:55:45 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_close(t_args *args)
{
	int	ind;

	ft_close_fd(&args->fd_in);
	ft_close_fd(&args->fd_out);
	ft_close_pipes(args);
	if (args->processes)
	{
		ind = 0;
		while (args->processes[ind])
		{
			if (args->processes[ind]->cmd)
				free(args->processes[ind]->cmd);
			ft_free_array((void **) args->processes[ind]->args);
			free(args->processes[ind]);
			ind++;
		}
		free(args->processes);
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
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 .. out\n", 2);
		exit(1);
	}
	args = ft_parse_args(argc, argv, envp);
	ft_execute_processes(&args, envp);
	ft_free_close(&args);
	ft_wait_for_processes();
}
