/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/20 16:00:26 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// This function prints an error message regarding correct usage
// of arguments then exits the program.
void	incorrect_args(void)
{
	err_and_exit("Correct usage: \n"
		"1) ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2 \n"
		"2) ./pipex here_doc LIMITER cmd cmd1 file");
}

// >> in here_doc usage means appending to text file
// so O_APPEND is used here
// This function facilitates opening of files in different
// opening modes with full permissions (octal 0777).
int	open_file(char *file, int open_mode)
{
	int	fd;

	fd = 0;
	if (open_mode == IN_FILE)
		fd = open(file, O_RDONLY, 0777);
	else if (open_mode == OUT_FILE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (open_mode == OUT_FILE_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		err_and_exit("Failed to open file.");
	return (fd);
}

// This function will read input from stdout character by character
// into a buffer until a newline character is encountered,
// then the line pointer passed in as an argument will point to
// buffer to update line in the here_doc function.
int	extract_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		bytes_read;

	buffer = ft_calloc(256, sizeof(char));
	if (!buffer)
		return (-1);
	i = 0;
	bytes_read = read(0, &c, 1);
	while (bytes_read > 0)
	{
		buffer[i] = c;
		i++;
		if (c == '\n')
			break ;
		bytes_read = read(0, &c, 1);
	}
	*line = buffer;
	return (bytes_read);
}
