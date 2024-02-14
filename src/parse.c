/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:02 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/14 22:08:22 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(char **envp)
{
	int		i;
	char	*path;

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
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char *path)
{
	char	**dirs;
	char	*cmd_path;
	int		ind;

	dirs = ft_split(path, ':');
	ind = 0;
	while (dirs[ind])
	{
		cmd_path = ft_strjoin(dirs[ind], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
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

void	ft_check_fd(int fd)
{
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

t_args	ft_parse_args(int argc, char **argv, char **envp)
{
	t_args		args;
	int			ind;
	char		*path;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 .. file2\n", 2);
		exit(1);
	}
	args.fd_in = open(argv[1], O_RDONLY);
	ft_check_fd(args.fd_in);
	args.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT);
	ft_check_fd(args.fd_out);
	path = ft_get_path(envp);
	ind = 2;
	args.processes = malloc(sizeof(t_process *) * (argc - 2));
	if (!args.processes)
		ft_exit_error(&args, "malloc failed");
	while (ind < argc - 1)
	{
		args.processes[ind - 2] = malloc(sizeof(t_process));
		args.processes[ind - 2]->cmd = ft_get_cmd_path(argv[ind], path);
		if (!args.processes[ind - 2]->cmd)
			ft_exit_error(&args, "command not found");
		ind++;
	}
	args.processes[ind - 2] = malloc(sizeof(t_process));
	args.processes[ind - 2]->cmd = NULL;
	free(path);
	return (args);
}
