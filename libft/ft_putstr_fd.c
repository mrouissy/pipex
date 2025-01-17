#include "libft.h"

void ft_putstr_fd(const char *msg, int fd)
{
	if (msg)
		write(fd, msg, ft_strlen(msg));
}
