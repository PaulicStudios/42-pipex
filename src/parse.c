/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:02 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/07 15:35:57 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_process	*ft_parse_process_infos(t_args *args, char *cmd, char *path)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	if (!process)
		ft_exit_error(args, "malloc failed");
	process->args = ft_split(cmd, ' ');
	if (!process->args)
		ft_exit_error(args, "split failed");
	process->cmd = ft_get_cmd_path(process->args[0], path, args);
	if (!process->cmd)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(process->args[0], 2);
		ft_putchar_fd('\n', 2);
	}
	process->pipe_fd_in[PIPE_READ] = -1;
	process->pipe_fd_in[PIPE_WRITE] = -1;
	process->pipe_fd_out[PIPE_READ] = -1;
	process->pipe_fd_out[PIPE_WRITE] = -1;
	return (process);
}

void	ft_handle_default(t_args *args, int argc, char **argv)
{
	args->fd_in = open(argv[1], O_RDONLY);
	ft_check_fd(args->fd_in);
	args->fd_out = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	ft_check_fd(args->fd_out);
}

void	ft_fill_command_args(t_args *args, char **argv, int argc, char **envp)
{
	int		ind;
	char	*path;

	path = ft_get_path(args, envp);
	ind = args->start_arg;
	args->processes = malloc(sizeof(t_process *) * (argc - args->start_arg));
	if (!args->processes)
	{
		free(path);
		ft_exit_error(args, "malloc failed");
	}
	while (ind < argc - 1)
	{
		args->processes[ind - args->start_arg]
			= ft_parse_process_infos(args, argv[ind], path);
		ind++;
	}
	args->processes[ind - args->start_arg] = NULL;
	free(path);
}

t_args	ft_parse_args(int argc, char **argv, char **envp)
{
	t_args	args;

	args.fd_in = -1;
	args.fd_out = -1;
	args.processes = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		ft_handle_here_doc(&args, argv, argc);
		args.start_arg = 3;
		args.process_len = argc - 4;
	}
	else
	{
		ft_handle_default(&args, argc, argv);
		args.start_arg = 2;
		args.process_len = argc - 3;
	}
	ft_fill_command_args(&args, argv, argc, envp);
	return (args);
}
