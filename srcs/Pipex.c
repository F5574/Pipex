/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:20 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/27 20:19:17 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
	int		status;
	int		pipe_fd[2];

	if (argc != 5 || (!*argv[2] && !*argv[3]))
		exits(NULL, 1, 1);
	pipex_init(&pipex, argv, envp, -1);
	if (pipe(pipe_fd) == -1)
		exits(pipex, 7, 7);
	pipex->fd[0][1] = pipe_fd[1];
	pipex->fd[1][0] = pipe_fd[0];
	child_p((t_fds){pipex->fd[0][0], pipex->fd[0][1], pipex->fd[1][0],
		pipex->fd[1][1]}, pipex, 0);
	close(pipex->fd[0][1]);
	child_p((t_fds){pipex->fd[1][0], pipex->fd[1][1], pipex->fd[0][0],
		pipex->fd[0][1]}, pipex, 1);
	close(pipex->fd[1][0]);
	waiting(pipex, &status);
	close(pipex->fd[1][1]);
	if (pipex->fd[0][0] != -1)
		close(pipex->fd[0][0]);
	exits(pipex, 10, status);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s 
//--trace-children=yes --track-fds=yes