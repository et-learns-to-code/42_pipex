/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/19 10:50:00 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	err_and_exit(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

// path and args don't have to be freed after execve is called
// because the process image will be replaced by the new
// program and previous memory will be deallocated by the system.
void	exec_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	path = fetch_path(args[0], env);
	if (!path)
	{
		free_double_arr(args);
		err_and_exit("Command not found.");
	}
	if ((execve(path, args, env)) == -1)
		err_and_exit("Failed to execute command.");
}

// F_OK | X_OK is a bitwise operation that checks that the file both
// exists and is executable.
char	*fetch_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*append_cmd;
	char	*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	append_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], append_cmd);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_double_arr(paths);
	free(append_cmd);
	return (path);
}

void	free_double_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
