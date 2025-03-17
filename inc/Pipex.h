/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:01:26 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/13 16:17:18 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <string.h>
# include <sys/wait.h>
 
// Structs -----------------------------

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


#endif