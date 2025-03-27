/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:01:26 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/27 20:20:49 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../inc/libft/libft.h"
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

// Structs --------------------------------------------------------------------

typedef struct s_pipe
{
	int		pid[2];
	int		fd[2][2];
	char	**comm[2];
	char	**envp;
	char	*path[2];
	char	**env;
}			t_pipe;

typedef struct s_fds
{
	int		input_r;
	int		input_w;
	int		output_r;
	int		output_w;
}			t_fds;

// Commands Parsing -----------------------------------------------------------

char	**split_command(char const *input_str, int i);

// Clean Pipex ----------------------------------------------------------------

void	exits(t_pipe *pipex, int type, int status);
void	check_access(t_pipe *pipex, char *path);

// Process --------------------------------------------------------------------

char	*create_path(t_pipe *pipex, int x, int i);
void	paths(t_pipe *pipex, int n, int i, int x);
void	pipex_init(t_pipe **pipex, char	**argv, char **envp, int i);
void	child_p(t_fds fds, t_pipe *pipex, int i);
void	waiting(t_pipe *pipex, int *status);

#endif