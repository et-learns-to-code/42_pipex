/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:12 by etien             #+#    #+#             */
/*   Updated: 2024/07/20 16:08:08 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// fcntl.h - open
// stdlib.h - exit, free
// sys/types.h - pid_t data type
// sys/wait.h - wait
// unistd.h - access, close, dup2, execve, fork, pipe

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_FILE 0
# define OUT_FILE 1
# define OUT_FILE_APPEND 2

// Util functions for mandatory part - utils_bonus.c
void	err_and_exit(char *message);
void	exec_cmd(char *cmd, char **env);
char	*fetch_path(char *cmd, char **env);
void	free_double_arr(char **arr);

// Util functions for bonus part - utils_extra_bonus.c
void	incorrect_args(void);
int		open_file(char *file, int open_mode);
int		extract_line(char **line);

#endif
