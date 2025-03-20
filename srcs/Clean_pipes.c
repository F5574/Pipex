/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clean_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:04:56 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/19 18:55:38 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

void	free_double_pointers(void **input, int max, int ctl)
{
	while (ctl <= max)
		free(input[ctl++]);
	free(input);
}

void	free_pipe(t_pipe *pipex, int status, int i, int x)
{
	while (status >= 6 && pipex->env[++i])
		;
	if (status >= 6)
		free_double_pointers((void **)pipex->env, i, 0);
	if (status >= 6 && pipex->path[0])
		free(pipex->path[0]);
	if (status >= 6 && pipex->path[0])
		free(pipex->path[0]);
	while (status >= 4 && ++x <= 1)
	{
		i = -1;
		while (pipex->comm[x][++i])
			;
		if (pipex->comm[x])
			free_double_pointers((void **)pipex->comm[x], i, 0);
	}
	if (pipex->fd[0][0] != -1)
		close(pipex->fd[0][0]);
	if (pipex->fd[1][1] != -1)
		close(pipex->fd[1][1]);
	free(pipex);
}

void	exits(t_pipe *pipex, int type, int status)
{
	if (type == 1)
		ft_printf("Incorrect format! accepted only:"
			"\" infile \"cmd1\" \"cmd2\" outfile \"\n");
	else if (type == 2)
		ft_printf("Allocation failure");
	else if (type == 3)
		perror("Open file in or out failure");
	else if (type == 4)
		ft_printf("Allocation failure for commands");
	else if (type == 5 || type == 6)
		ft_printf("Wrong path");
	else if (type == 7)
		perror("Pipe failure");
	else if (type == 8)
		perror("Fork failure");
	else if (type == 9)
		perror("Command not found");
	if (type > 2)
		free_pipe(pipex, type, -1, -1);
	exit(status);
}
