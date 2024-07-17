/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:48:09 by etien             #+#    #+#             */
/*   Updated: 2024/07/17 16:06:38 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	execute(char **av, char **env)
{
	char	*path;
	char	**args;

	if execve(path, args, env);





}

char *fetch_path(char **av, char **env)
{

}
