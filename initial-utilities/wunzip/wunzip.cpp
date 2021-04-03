#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	if(argc < 2){
		write(STDOUT_FILENO, "wunzip: file1 [file2 ...]\n", 26);
		exit(1);
	}
	
	int fd;
	int readRtr;
	int32_t block_size;
	char block_char;
	
	for(int i = 1; i < argc; i++){		
		fd = open(argv[i], O_RDONLY);
		if(fd < 0){
			write(STDOUT_FILENO, "wunzip: cannot open file\n", 25);
			exit(1);
		}
		
		if((readRtr = read(fd, &block_size, sizeof(int32_t))) == 0){
			close(fd);
			continue;
		}
		
		do{
			read(fd, &block_char, 1);
			char block[block_size];
			for(int j = 0; j < block_size; j++){
				block[j] = block_char;
			}
			write(STDOUT_FILENO, block, block_size);
		}
		while((readRtr = read(fd, &block_size, sizeof(int32_t))) > 0);

		close(fd);
	}
	
	exit(0);
}