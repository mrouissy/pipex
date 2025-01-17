#include "pipex.h"

// environment variables
char *get_env(char **env)
{
	int i = 0;
	char *name = "PATH";
	while (env[i]) {
		if (ft_strcmp(ft_substr(env[i], 0, 4), name) == 0)
			return (env[i] + 5);
			i++;
	}
	return (0);
}

// all path
char **get_paths(char **env)
{
	char **paths;
	char *en = get_env(env);
	paths = ft_split(en, ':');
	return (paths);
}

char *newstrjoin(char *str1, char *str2, char *str3)
{
	char *str;
    str = ft_strjoin((const char *)str1, (const char *)str2);
    str = ft_strjoin((const char *)str, str3);
    return (str);
}

// exec path
char *get_path(char **paths, char *cmd)
{
    char *cmdpath;
    int i = 0;
    while (paths[i]) {
        cmdpath = newstrjoin(paths[i], "/", cmd);
        if (access(cmdpath, F_OK | X_OK) == 0)
            return (cmdpath);
        i++;
    }
    return (cmd);
}

int open_file(char *path, int fd)
{
    int ret;
    if (fd == 0)
        ret = open(path, O_RDONLY, 0777);
    else if (fd == 1)
        ret = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777);
    else
        exit(0);
    return ret;
}

// execute cmd
void ft_exec(char **cmd, char *execpath, char **env)
{
	if (execve(execpath, cmd, env) == -1)
		printf("command not found: \"%s\"\n", cmd[0]);
}

// parent process
void ft_parent(char **env, char *file, char **cmd, int *fds, char *execpath)
{
	int fd = open_file(file, 1);
	dup2(fd, 1);
	dup2(fds[0], 0);
	close(fds[1]);
	ft_exec(cmd, execpath, env);
}

// child process
void ft_child(char **env, char *file, char **cmd, int *fds, char *execpath)
{
	int fd = open_file(file, 0);
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[0]);
	ft_exec(cmd, execpath, env);
}

int main(int ac, char *av[], char **env)
{
	if (ac != 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(-1);
	}

	char **paths = get_paths(env);
	int p_fd[2];
	pid_t id;

	if (pipe(p_fd) == -1)
		exit(-1);
	id = fork();
	if (id == -1)
		exit(-1);
	if (!id)
	{
		char **cmd1 = ft_split(av[2], ' ');
		char *execpath1 = get_path(paths, cmd1[0]);
		ft_child(env, av[1], cmd1, p_fd, execpath1);
	}
	else
	{
		char **cmd2 = ft_split(av[3], ' ');
		char *execpath2 = get_path(paths, cmd2[0]);
		ft_parent(env, av[4], cmd2, p_fd, execpath2);
	}

	return 0;
}
