
#include "pipex.h"

// execute cmd
static void	ft_exec(char **cmd, char *execpath, char **env)
{
	if (execve(execpath, cmd, env) == -1)
		printf("command not found: \"%s\"\n", cmd[0]);
}
// aray fiha path o cmd
#include "pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
// Assume get_paths, ft_split, get_path, open_file, ft_exec are defined elsewhere

static void ft_parent(char **env, char **av, int *fds)
{
	int	fd;
	char **cmd2;
	char *execpath;
	char **paths;

	paths = get_paths(env);
	cmd2 = ft_split(av[4], ' ');
	execpath = get_path(paths, cmd2[0]);
	fd = open_file(av[4], 1);
    if (fd == -1)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    if (dup2(fds[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fds[1]);
    ft_exec(cmd2, execpath, env);
}

static void ft_child(char **env, char **av, int *fds)
{
    int fd;
    char **cmd1;
    char *execpath;
    char **paths;

    paths = get_paths(env);
    cmd1 = ft_split(av[2], ' ');
    execpath = get_path(paths, cmd1[0]);
    fd = open_file(av[1], 0);
    if (fd == -1)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    if (dup2(fds[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fds[0]);
    ft_exec(cmd1, execpath, env);
}

int main(int ac, char *av[], char **env)
{
    int p_fd[2];
    pid_t id;

    if (ac != 5)
    {
        fprintf(stderr, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(p_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    id = fork();
    if (id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (id == 0)
        ft_child(env, av, p_fd);
    else
    {
        ft_parent(env, av, p_fd);
        close(p_fd[0]);
        close(p_fd[1]);
        waitpid(id, NULL, 0);
    }
    return 0;
}
