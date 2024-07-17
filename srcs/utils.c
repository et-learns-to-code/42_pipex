/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/17 18:43:47 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	err_and_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	exec_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	path = fetch_path(cmd, env);
	if (!path)
		err_and_exit("Path to command not found.");
	if ((execve(path, args, env)) == -1)
	{
		err_and_exit("Failed to execute command.");
	}
}

// F_OK | X_OK is a bitwise operation that checks that the file both
// exists and is executable.
char *fetch_path(char *cmd, char **env)
{
	int i;
	int j;
	char **paths;
	char *append_cmd;
	char *path;

	append_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			j = -1;
			while (paths[++j])
			{
				path = ft_strjoin(paths[j], append_cmd);
				if (access(path, F_OK | X_OK))
					return (path);
			}
		}
		i++;
	}
	return (NULL);
}
