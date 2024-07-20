/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/20 10:56:14 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	incorrect_args(void)
{
	err_and_exit("Correct usage: \n"
		"1) ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2 \n"
		"2) ./pipex here_doc LIMITER cmd cmd1 file");
}

// >> in here_doc command means appending to text file
// so O_APPEND is used for here_doc
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

// this function will read input from stdin character by character
// into a buffer until a newline character is encountered,
// then the line pointer will point to buffer to update
// line in here_doc function
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
	while (((bytes_read = read(0, &c, 1)) > 0))
	{
		buffer[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	*line = buffer;
	return (bytes_read);
}
