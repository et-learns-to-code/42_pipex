/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by etien             #+#    #+#             */
/*   Updated: 2024/07/17 13:04:41 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>

// pid_t is a data type available under the <sys/types.h> library specifically
// used to store process ids.
int main(int argc, char **argv, char **envp)
{
	int i = 0;
    while (envp[i] != NULL) {
        printf("%s\n", envp[i]);
        i++;
    }
    return 0;
}


/*
// WHAT TO DO
- have a parent and child function, they will execute and be replaced by the process image of the respective executables.
parent and child will open the different end of the pipes and will dup2 to replace stdout and stdin. close the side of the
pipe that is not in use.

- have a controller function to facilitate opening and opening files in the correct mode (O_RDONLY or O_WRONLY | O_CREAT
| O_TRUNC) and with the correct access permissions (0777)

- have a function that can extract the paths in the $PATH variable (**), terminate each path with a '/' and append the
executable name at the end then try each path with the access function to see that the file both exists and is
an executable - return the correct path to be executed

- remember to free whenever strjoin, substr or split is called and the variable is no longer in use.
you can create a helper function for this (esp. to free the 2D arrays).

- remember to error check for read, write, fork and pipe

// FOR BONUS
- utils part identical except append used here for heredoc portion:
if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);

// HEREDOC PROCESSING
- in main part, detect for "here_doc" string - number of arguments will be different when here_doc is being detected

- heredoc only needs an fd_out, no need fd_in
fd_out = open_file(av[ac - 1], 2);
(ac - 1) to get last argument, and 2 is arbitrary number but will tie in with utils to do appending

// NORMAL PROCESSING
- dup2 to make fd_in replace stdin
- only execute the last command in main body; the rest will be handled under do_pipe function
- do_pipe function: execution will be delegated to child process - parent handle
- always redirect before executing in child process
*/




