/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:05:12 by etien             #+#    #+#             */
/*   Updated: 2024/07/17 18:32:32 by etien            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void error(char *message);
void exec_cmd(char **av, char **env);
char *fetch_path(char *cmd, char **env);

#endif
