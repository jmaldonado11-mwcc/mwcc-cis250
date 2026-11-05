#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("needs to be in format:\n./caseconv (upper/lower) filename\n");
		return 1;
	}
	int mode = 0;
	if(strcmp(argv[1], "upper") == 0)
	{
		mode++;
	}
	else if(strcmp(argv[1], "lower") == 0)
	{
		mode--;
	}else
	{
		printf("Invalid Command\n");
		return 1;
	}

	int fd = open(argv[2], O_RDONLY);

	if (fd < 0)
	{
		perror("Error opening file\n");
		return 1;
	}

	struct stat sb;
	if(fstat(fd, &sb) == -1)
	{
		perror("Can't get file size\n");
		close(fd);
		return 1;
	}
	else if(sb.st_size == 0)
	{
		printf("Empty file\n");
		close(fd);
		return 1;
	}

	printf("File size: %ld\n", sb.st_size);

	const char *out_filename = "newfile.txt";

	int out_fd = open(out_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(out_fd == -1)
	{
		perror("Error making copy");
		close(fd);
		return 1;
	}

	for (int i = 0; i < sb.st_size; i++)
	{
		if(write(out_fd, "\0", 1) != 1)
		{
			perror("Error writing output");
			close(fd);
			close(out_fd);
			return 1;
		}
	}
        char *src = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	char *memfile = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, out_fd, 0);

	if(mode == 1)
	{
		for(int i = 0; i < sb.st_size; i++)
		{
			memfile[i] = toupper(src[i]);
			printf("%c", memfile[i]);
		}
	}
	else if(mode == -1)
	{
		for(int i = 0; i < sb.st_size; i++)
                {
                        memfile[i] = tolower(src[i]);
                        printf("%c", memfile[i]);
                }
	}

        munmap(src, sb.st_size);
	munmap(memfile, sb.st_size);
	close(fd);
        close(out_fd);
}
