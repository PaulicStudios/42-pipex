/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:22:52 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/07 15:36:07 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	ft_handle_here_doc(t_args *args, char **argv, int argc)
{
	char	*line;
	int		fd_pipe[2];

	args->limiter = argv[2];
	args->fd_out = open(argv[argc - 1], O_APPEND | O_WRONLY | O_CREAT, 0644);
	ft_check_fd(args->fd_out);
	if (pipe(fd_pipe) == -1)
		ft_exit_error(args, "Error creating pipe");
	args->fd_in = fd_pipe[PIPE_READ];
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, args->limiter, ft_strlen(args->limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_pipe[PIPE_WRITE]);
		free(line);
	}
	close(fd_pipe[PIPE_WRITE]);
}
