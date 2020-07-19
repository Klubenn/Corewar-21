#include "../includes/asm.h"

void print_ascii(unsigned char *c, int fd)
{
	int i;

	i = 0;
	printf("     ");
	while(i < 16)
	{
		if (c[i] >= 32 && c[i] <= 126)
			printf("%c", c[i]);
		else
			printf(".");
		i++;
	}
}

void print_file(char *new_file)
{
	unsigned char	c[16];
	int		i;
	int		j;
	int		fd;

	i = 0;
	j = 0;
	fd = open(new_file, O_RDONLY);
	while(read(fd, &(c[i]), 1))
	{
		printf("%02x", (int)c[i]);
		i++;
		if (i % 2 == 0)
		{
			j++;
			if(j == 8)
			{
				i = 0;
				j = 0;
				print_ascii(c, fd);//print visible characters
				printf("\n");
			}
			else
				printf(" ");
		}
	}
	close(fd);
}
