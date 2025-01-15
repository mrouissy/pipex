#include "libft.h"

void ft_putstr_fd(char *msg, int fd)
{
	if (msg)
		write(fd, msg, ft_strlen(msg));
}
