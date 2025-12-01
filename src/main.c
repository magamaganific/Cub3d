#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/cube3d.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define WIDTH 900
#define HEIGHT 900

void print_accepted_input(void)
{
	printf("Accepted input: \n	./Game [MAP PATH]\n");
	printf("		(maps available in the \"maps\" directory2)\n");
}

int main(int ac, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (ac != 2 || fd == -1)
	{
		print_accepted_input();
		return (-1);
	}

	close(fd);
}