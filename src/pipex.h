/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouissy <mrouissy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:56:10 by mrouissy          #+#    #+#             */
/*   Updated: 2025/01/19 04:57:04 by mrouissy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>

char	*ft_get_paths(char **env);
char	*ft_get_path(char **env, char **av, int j);

void	ft_exec(char *path, char **cmd, char **env);

int		ft_open_file(char *path, int fd);

#endif
