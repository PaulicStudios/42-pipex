/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:02 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/25 20:13:12 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(t_args *args, char **envp)
{
	int		i;
	char	*path;

	if (!envp)
		ft_exit_error(args, "no environment");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			return (path);
		}
		i++;
	}
	ft_exit_error(args, "no path in environment");
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char *path, t_args *args)
{
	char	**dirs;
	char	*cmd_path;
	char	*tmp;
	int		ind;

	dirs = ft_split(path, ':');
	ind = 0;
	while (dirs[ind])
	{
		cmd_path = ft_strjoin(dirs[ind], "/");
		if (!cmd_path)
		{
			ft_free_array((void **) dirs);
			ft_exit_error(args, "malloc failed");
		}
		tmp = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!tmp)
		{
			ft_free_array((void **) dirs);
			ft_exit_error(args, "malloc failed");
		}
		cmd_path = tmp;
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_array((void **) dirs);
			return (cmd_path);
		}
		free(cmd_path);
		ind++;
	}
	ft_free_array((void **) dirs);
	return (NULL);
}

t_process	*ft_parse_process_infos(t_args *args, char *cmd, char *path)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	if (!process)
		ft_exit_error(args, "malloc failed");
	process->args = ft_split(cmd, ' ');
	process->cmd = ft_get_cmd_path(process->args[0], path, args);
	if (!process->cmd)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(process->args[0], 2);
		ft_putchar_fd('\n', 2);
	}
	return (process);
}

void	ft_handle_default(t_args *args, int argc, char **argv)
{
	args->fd_in = open(argv[1], O_RDONLY);
	ft_check_fd(args->fd_in, args);
	args->fd_out = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	ft_check_fd(args->fd_out, args);
}

void	ft_fill_command_args(t_args *args, int start_arg, char **argv, int argc, char **envp)
{
	int		ind;
	char	*path;

	path = ft_get_path(args, envp);
	ind = start_arg;
	args->processes = malloc(sizeof(t_process *) * (argc - start_arg));
	if (!args->processes)
	{
		free(path);
		ft_exit_error(args, "malloc failed");
	}
	while (ind < argc - 1)
	{
		args->processes[ind - start_arg] = ft_parse_process_infos(args, argv[ind], path);
		ind++;
	}
	args->processes[ind - start_arg] = NULL;
	free(path);
}

t_args	ft_parse_args(int argc, char **argv, char **envp)
{
	t_args	args;
	int		start_arg;

	args.fd_in = -1;
	args.fd_out = -1;
	args.processes = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		ft_handle_here_doc(&args, argv, argc);
		start_arg = 3;
		args.process_len = argc - 4;
	}
	else
	{
		ft_handle_default(&args, argc, argv);
		start_arg = 2;
		args.process_len = argc - 3;
	}
	ft_fill_command_args(&args, start_arg, argv, argc, envp);
	return (args);
}
