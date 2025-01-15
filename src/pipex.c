#include "../libft/libft.h"
#include "pipex.h"
int main(int ac, char const **av)
{
	if(ac != 4)
	{
		ft_putstr_fd("Error in input commande must be like this :\n$> < file1 cmd1 | cmd2 > file2",1);
		return (1);
	}
	int fd1 = open(av[1], O_RDONLY);
	int fd2 = open(av[4], O_WRONLY);
	dup2(fd2,1);
	
	return 0;
}
