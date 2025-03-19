/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:42:13 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/19 19:34:17 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

char	*create_path(t_pipe *pipex, int x, int i)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(pipex->envp[i], "/");
	path = ft_strjoin(temp, pipex->comm[x][0]);
	if (temp)
		free(temp);
	if (!path)
		exits(pipex, 6, 6);
	return (path);
}

void	paths(t_pipe *pipex, int n, int i, int x)
{
	int		res;
	char	*path;

	while (++x < n)
	{
		i = -1;
		res = 1;
		while (pipex->envp[++i] && res)
		{
			path = create_path(pipex, x, i);
			res = access(path, F_OK);
			if (!res)
				pipex->path[x] = ft_strdup(path);
			else if (!pipex->envp[i + 1])
				pipex->path[x] = ft_strdup(pipex->comm[x][0]);
			free(path);
		}
	}
}

void	pipex_init(t_pipe **pipex, char	**argv, char **envp, int i)
{
	*pipex = malloc(sizeof(t_pipe));
	if (!pipex)
		exits(*pipex, 2, 2);
	(*pipex)->fd[0][0] = open(argv[1], O_RDONLY);
	(*pipex)->fd[1][1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if ((*pipex)->fd[1][1] == -1)
		exits(*pipex, 3, 3);
	(*pipex)->comm[0] = Split_command(argv[2]);
	(*pipex)->comm[1] = Split_command(argv[3]);
	if (!*((*pipex)->comm[0]) || !*((*pipex)->comm[1]))
		exits(*pipex, 4, 4);
	(*pipex)->envp = NULL;
	while (envp[++i] && !(*pipex)->envp)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			(*pipex)->envp = ft_split(envp[i] + 5, ':');
	}
	if (!(*pipex)->envp)
		clean_pipes_exit(*pipex, 5, 5);
	find_paths(*pipex, 2);
	(*pipex)->env = envp;
}
