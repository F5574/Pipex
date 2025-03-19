/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:20 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/19 19:33:55 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipe	*pipex;
	int		status;
	int		pipe_fd[2];

	if (argc != 5 || !argv[2][0] || !argv[3][0])
		exits(NULL, 1,1);
	pipex_init(&pipex, argv, envp, -1);
}