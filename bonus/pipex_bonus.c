/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by etien             #+#    #+#             */
/*   Updated: 2024/07/19 12:55:02 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	create_child_process(char *cmd, char **env);

// cmd_index variable is used to mark the command to be created in
// the child process.
// The main function is different from the mandatory part by inclusion
// of a while loop that will create a child process for each command in
// the pipe chain.
int	main(int ac, char **av, char **env)
{
	int	cmd_index;
	int	infile;
	int	outfile;

	if (ac < 5)
		err_and_exit("Correct usage: \n"
			"1) ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2 \n"
			"2) ./pipex here_doc LIMITER cmd cmd1 file");
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		cmd_index = 3;
		outfile = open_file(av[ac - 1], OUT_FILE_APPEND);
	}
	else
	{
		cmd_index = 2;
		infile = open_file(av[1], IN_FILE);
		outfile = open_file(av[ac - 1], OUT_FILE);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	while (cmd_index < ac - 2)
		create_child_proces(av[cmd_index++], env);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec_cmd(av[ac - 2], env);
	return (EXIT_SUCCESS);
}

void	create_child_process(char *cmd, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		err_and_exit("A pipe error occurred.");
	pid = fork();
	if (pid == -1)
		err_and_exit("A fork error occurred.");
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_cmd(cmd, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		wait(NULL);
	}
}

void here_doc()
/*
// WHAT TO DO
- have a parent and child function, they will execute and be replaced by the
process image of the respective executables.
parent and child will open the different end of the pipes and will dup2 to
replace stdout and stdin. close the side of the
pipe that is not in use.

- have a controller function to facilitate opening and opening files in the
correct mode (O_RDONLY or O_WRONLY | O_CREAT
| O_TRUNC) and with the correct access permissions (0777)

- have a function that can extract the paths in the $PATH variable (**),
terminate each path with a '/' and append the
executable name at the end then try each path with the access function to see
that the file both exists and is
an executable - return the correct path to be executed

- remember to free whenever strjoin or split is called and the
variable is no longer in use.
you can create a helper function for this (esp. to free the 2D arrays).

- remember to error check for read, write, fork and pipe

// FOR BONUS
- utils part identical except append used here for heredoc portion:
if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);

// HEREDOC PROCESSING
- in main part, detect for "here_doc" string - number of arguments will be
different when here_doc is being detected

- heredoc only needs an fd_out, no need fd_in
fd_out = open_file(av[ac - 1], 2);
(ac - 1) to get last argument, and 2 is arbitrary number but will tie in with
utils to do appending

// NORMAL PROCESSING
- dup2 to make fd_in replace stdin
- only execute the last command in main body; the rest will be handled under
do_pipe function
- do_pipe function: execution will be delegated to child process - parent
handle
- always redirect before executing in child process
*/
