#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	if(argc < 2){
		write(STDOUT_FILENO, "wzip: file1 [file2 ...]\n", 24);
		exit(1);
	}
	
	int fd;
	int readRtr;
	char buf;
	std::string block;
	int32_t block_size;
	
	for(int i = 1; i < argc; i++){		
		fd = open(argv[i], O_RDONLY);
		if(fd < 0){
			write(STDOUT_FILENO, "wzip: cannot open file\n", 23);
			exit(1);
		}
		
		if((readRtr = read(fd, &buf, 1)) == 0){
			close(fd);
			continue;
		}	
		
		do{
			if(block.size() == 0){
				block += buf;
				continue;
			}
			
			if(block[0] != buf){
				block_size = (int32_t)block.size();
				write(STDOUT_FILENO, &block_size, sizeof(int32_t));
				write(STDOUT_FILENO, &block[0], 1);
				block.clear();
				
				block += buf;
			}
			else
				block += buf;
		}
		while((readRtr = read(fd, &buf, 1)) > 0);
		
		close(fd);
	}
	
	block_size = (int32_t)block.size();
	write(STDOUT_FILENO, &block_size, sizeof(int32_t));
	write(STDOUT_FILENO, &block[0], 1);
	
	exit(0);
}