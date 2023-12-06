/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:01:37 by pgrossma          #+#    #+#             */
/*   Updated: 2023/12/06 15:09:44 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	args = ft_parse(argc, argv);

	char	**cmd1 = ft_split(args.cmds[0], ' ');
	execve(cmd1[0], cmd1, envp);

	// printf("fd_in: %d\n", args.fd_in);
	// printf("fd_out: %d\n", args.fd_out);
	// printf("cmd1: %s\n", args.cmds[0]);
	// printf("cmd2: %s\n", args.cmds[1]);
	free(args.cmds);
}
