/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/20 11:39:52 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// This function prints a custom error message before exiting the
// program with EXIT_FAILURE (code 1).
void	err_and_exit(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

// path doesn't have to be freed after execve is called
// because the process image will be replaced by the new
// program.
// This function formulates the arguments (path and args) to call the
// execve funtion that will execute the command.
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
// This function will fix together the path to the command by
// drawing from the $PATH environment variable, concatenating the command
// and testing until a correct path is found.
// String manipulation: {path} + {/} + {cmd}
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

// A helper function to free double arrays for proper memory management.
// (e.g. paths and args)
void	free_double_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
