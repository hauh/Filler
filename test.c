#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char buf;
	int fd;

	fd = open("testmap", O_RDONLY);
	while (read(fd, &buf, 1))
		printf("%c", buf);
}
