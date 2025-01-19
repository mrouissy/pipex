/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouissy <mrouissy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:55:03 by mrouissy          #+#    #+#             */
/*   Updated: 2025/01/19 05:30:03 by mrouissy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_substr(env[i], 0, 4), "PATH") == 0)
			return (env[i] + 5);
		i++;
	}
	ft_putstr_fd("faild", 2);
	exit(EXIT_FAILURE);
	return (0);
}

char	*ft_get_path(char **env, char **av, int j)
{
	char	**paths;
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	paths = ft_split(ft_get_env(env), ':');
	cmd = ft_split(av[j], ' ');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	ft_putstr_fd("command not found\n", 2);
	exit(EXIT_FAILURE);
	return (0);
}

void	ft_exec(char *path, char **cmd, char **env)
{
	if (execve(path, cmd, env) == -1)
	{
		ft_putstr_fd("ERROR", 2);
		exit(EXIT_FAILURE);
	}
}

int	ft_open_file(char *path, int fd)
{
	int	ret;

	ret = -1;
	if (fd == 0)
		ret = open(path, O_RDONLY);
	else if (fd == 1)
		ret = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		exit(EXIT_FAILURE);
	return (ret);
}
