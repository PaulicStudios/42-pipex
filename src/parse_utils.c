/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:50:46 by pgrossma          #+#    #+#             */
/*   Updated: 2024/02/26 14:57:08 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_cmd_path(t_args *args, char **dirs, char *cmd, int ind)
{
	char	*cmd_path;
	char	*tmp;

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
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char *path, t_args *args)
{
	char	**dirs;
	char	*cmd_path;
	int		ind;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_split(path, ':');
	ind = 0;
	while (dirs[ind])
	{
		cmd_path = ft_check_cmd_path(args, dirs, cmd, ind);
		if (cmd_path)
			return (cmd_path);
		ind++;
	}
	ft_free_array((void **) dirs);
	return (NULL);
}

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
