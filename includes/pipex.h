/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:12 by etien             #+#    #+#             */
/*   Updated: 2024/07/18 10:03:50 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// fcntl.h - open
// stdio.h - perror
// sys/types.h - pid_t data type

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void err_and_exit(char *message);
void exec_cmd(char *cmd, char **env);
char *fetch_path(char *cmd, char **env);
void free_double_arr(char** arr);

#endif
