
#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

char	*get_env(char **env);
char	**get_paths(char **env);
char	*newstrjoin(char *str1, char *str2, char *str3);
char	*get_path(char **paths, char *cmd);
int		open_file(char *path, int fd);

#endif
