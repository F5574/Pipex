/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:01:26 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/19 19:32:59 by gvon-ah-         ###   ########.fr       */
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
	int 	output_w;
}			t_fds;

// Commands Parsing -----------------------------------------------------------

char **Split_command(char const *input_str);

// Clean Pipex ----------------------------------------------------------------

void	exits(t_pipe *pipex, int type, int status);

// Process --------------------------------------------------------------------

void	pipex_init(t_pipe **pipex, char	**argv, char **envp, int i);

#endif