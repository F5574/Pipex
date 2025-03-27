/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvon-ah- <gvon-ah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:42:13 by gvon-ah-          #+#    #+#             */
/*   Updated: 2025/03/27 16:00:39 by gvon-ah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Pipex.h"

char	*create_path(t_pipe *pipex, int x, int i)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(pipex->envp[i], "/");
	if (!pipex->comm[x][0])
		path = temp;
	else
		path = ft_strjoin(temp, pipex->comm[x][0]);
	if (temp && temp != path)
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
	(*pipex)->fd[1][1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((*pipex)->fd[1][1] == -1)
		exits(*pipex, 3, 3);
	(*pipex)->comm[0] = split_command(argv[2], 0);
	(*pipex)->comm[1] = split_command(argv[3], 0);
	if (!*((*pipex)->comm[0]) && !*((*pipex)->comm[1]))
		exits(*pipex, 4, 4);
	(*pipex)->envp = NULL;
	while (envp[++i] && !(*pipex)->envp)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			(*pipex)->envp = ft_split(envp[i] + 5, ':');
	}
	if (!(*pipex)->envp)
		exits(*pipex, 5, 5);
	paths(*pipex, 2, -1, -1);
	(*pipex)->env = envp;
}

void	child_p(t_fds fds, t_pipe *pipex, int i)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		exits(pipex, 8, 8);
	if (pipex->pid[i] == 0)
	{
		if (fds.output_r != -1)
			close(fds.output_r);
		if (fds.output_w != -1)
			close(fds.output_w);
		dup2(fds.input_r, STDIN_FILENO);
		if (fds.input_r != -1)
			close(fds.input_r);
		else
		{
			close(0);
			close(fds.input_w);
			exits(pipex, 9, 127);
		}
		dup2(fds.input_w, STDOUT_FILENO);
		if (fds.input_w != -1)
			close(fds.input_w);
		if (execve(pipex->path[i], pipex->comm[i], pipex->env) == -1)
			exits(pipex, 9, 127);
	}
}

void	waiting(t_pipe *pipex, int *status)
{
	int	pid;
	int	exit_status;

	pid = wait(&exit_status);
	if (pid == pipex->pid[0])
		wait(&exit_status);
	else
		wait(NULL);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
}
