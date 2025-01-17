#include "pipex.h"
// environment variables
char	*get_env(char **env)
{
	int i = 0;
	char *name = "PATH";
	char *tofind;
	while (env[i])
	{
		if(ft_strcmp(ft_substr(env[i],0,4),name) == 0)
			return (env[i] + 5);
		i++;
	}
	return (0);
}
//all path
char **get_paths(char **env)
{
	char **paths;
	char *en = get_env(env);
	paths = ft_split(en, ':');
	return (paths);
}

char *newstrjoin(char *str1, char *str2, char *str3)
{
	char	*str;

	str = ft_strjoin((const char *) str1, (const char *) str2);
	str = ft_strjoin((const char *)str, str3);
	return (str);
}
//exec path
char *get_path(char **paths, char* cmd)
{
	char *cmdpath;
	int i = 0;
	while (paths[i])
	{
		cmdpath = newstrjoin(paths[i],"/",cmd);
		if(access(cmdpath,F_OK | X_OK )== 0)
			return (cmdpath);
		i++;
	}
	return (cmd);
}


int main(int ac, char const *av[], char **env)
{
	char **paths = get_paths(env);
	int i = 0;
	char **cmd = ft_split(av[1], ' ');
	char *execpath = get_path(paths,cmd[0]);
	if(execve(execpath,cmd,env)== -1)
		printf("commande not founf");
	return 0;
}
