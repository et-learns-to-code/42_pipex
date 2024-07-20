/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by etien             #+#    #+#             */
/*   Updated: 2024/07/20 16:21:30 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	handle_files(int ac, char **av, int *cmd_index, int *outfile);
void	here_doc(int ac, char *limiter);
void	here_doc_input(int pipefd[2], char *limiter);
void	create_child_process(char *cmd, char **env);

// cmd_index variable is used to mark the command to be created in
// the child process.
// The bonus part program is different from the mandatory part by inclusion
// of a while loop that will create a child process for each command
// (except the last one) in the pipe chain.
// After the while loop, the final command is executed in the body of
// the main program.
int	main(int ac, char **av, char **env)
{
	int	cmd_index;
	int	outfile;

	if (ac < 5)
		incorrect_args();
	handle_files(ac, av, &cmd_index, &outfile);
	while (cmd_index < ac - 2)
		create_child_process(av[cmd_index++], env);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec_cmd(av[ac - 2], env);
	return (EXIT_SUCCESS);
}

// This function handles the opening of files.
// if: handles processing with here_doc
// else: handles normal processing with an infile
void	handle_files(int ac, char **av, int *cmd_index, int *outfile)
{
	int	infile;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		*cmd_index = 3;
		*outfile = open_file(av[ac - 1], OUT_FILE_APPEND);
		here_doc(ac, av[2]);
	}
	else
	{
		*cmd_index = 2;
		infile = open_file(av[1], IN_FILE);
		*outfile = open_file(av[ac - 1], OUT_FILE);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
}

// This function handles the processing for here_doc.
// Pipe and fork are used to accumulate all lines from the
// here_doc in the child process first before passing it in one go to
// the parent process.
void	here_doc(int ac, char *limiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (ac < 6)
		incorrect_args();
	if (pipe(pipefd) == -1)
		err_and_exit("A pipe error occurred.");
	pid = fork();
	if (pid == -1)
		err_and_exit("A fork error occurred.");
	else if (pid == 0)
		here_doc_input(pipefd, limiter);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		wait(NULL);
	}
}

// Helper function to here_doc that runs its child process
// of collecting input from stdout.
// extract_line function will fetch the next line and the line will be
// appended via write function to the pipe's write end until the limiter
// string is encountered.
void	here_doc_input(int pipefd[2], char *limiter)
{
	char	*line;

	close(pipefd[0]);
	while (extract_line(&line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

// This function creates a pipe then forks the process.
// The child process will execute the command and output to pipe write end.
// The parent process will wait for the child to terminate
// and read its input from the pipe read end.
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
- utils part identical except append used when opening files for heredoc portion:
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

- only execute the last command in main body; the rest will be handled
under child processes

- always redirect stdin and stdout before executing in child process
*/
