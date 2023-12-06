/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:20:02 by pgrossma          #+#    #+#             */
/*   Updated: 2023/12/06 14:55:21 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_fd(int fd)
{
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

t_args	ft_parse(int argc, char **argv)
{
	t_args	args;
	int		i;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	args.fd_in = open(argv[1], O_RDONLY);
	ft_check_fd(args.fd_in);
	args.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT);
	ft_check_fd(args.fd_out);
	i = 2;
	args.cmds = malloc(sizeof(char *) * argc - 2);
	while (i < argc - 1)
	{
		args.cmds[i - 2] = argv[i];
		i++;
	}
	return (args);
}
