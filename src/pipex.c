/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouissy <mrouissy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:54:51 by mrouissy          #+#    #+#             */
/*   Updated: 2025/01/19 05:59:38 by mrouissy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(char **env, char **av, int *fds)
{
	char	**cmd;
	int		fd;
	char	*path;

	cmd = ft_split(av[2], ' ');
	fd = ft_open_file(av[1], 0);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	path = ft_get_path(env, av, 2);
	if (dup2(fd, 0) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[1], 1) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
	close(fd);
	ft_exec(path, cmd, env);
}

void	ft_parent(char **env, char **av, int *fds)
{
	int		fd;
	char	*path;
	char	**cmd;

	cmd = ft_split(av[3], ' ');
	path = ft_get_path(env, av, 3);
	fd = ft_open_file(av[4], 1);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	path = ft_get_path(env, av, 3);
	if (dup2(fd, 1) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[0], 0) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
	close(fds[1]);
	ft_exec(path, cmd, env);
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	id;

	if (ac != 5)
	{
		ft_putstr_fd("./pipex <infile> <cmd1> <cmd2> <outfile> ", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(fds) == -1)
	{
		ft_putstr_fd("Error creating pipe", 2);
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (!id)
		ft_child(env, av, fds);
	wait(NULL);
	ft_parent(env, av, fds);
}
