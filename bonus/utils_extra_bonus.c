/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/19 11:31:45 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// >> in here_doc command means appending to text file
// so O_APPEND is used for here_doc
int	open_file(char *file, int open_mode)
{
	int	fd;

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
// then the line pointer will be moved to the buffer to update
// the line into the here_doc function
void extract_line(char **line)
{





}
