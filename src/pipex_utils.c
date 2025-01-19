
#include "pipex.h"

// environment variables
char	*get_env(char **env)
{
	int		i;
	char	*name;

	name = "PATH";
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_substr(env[i], 0, 4), name) == 0)
			return (env[i] + 5);
		i++;
	}
	return (0);
}

// all path
char	**get_paths(char **env)
{
	char	**paths;
	char	*en;

	en = get_env(env);
	paths = ft_split(en, ':');
	return (paths);
}

char	*newstrjoin(char *str1, char *str2, char *str3)
{
	char	*str;

	str = ft_strjoin((const char *)str1, (const char *)str2);
	str = ft_strjoin((const char *)str, str3);
	return (str);
}

// exec path
char	*get_path(char **paths, char *cmd)
{
	char	*cmdpath;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmdpath = newstrjoin(paths[i], "/", cmd);
		if (access(cmdpath, F_OK | X_OK) == 0)
			return (cmdpath);
		i++;
	}
	return (cmd);
}

int	open_file(char *path, int fd)
{
	int	ret;

	ret = 0;
	if (fd == 0)
		ret = open(path, O_RDONLY);
	else if (fd == 1)
		ret = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	else
		exit(0);
	return (ret);
}
