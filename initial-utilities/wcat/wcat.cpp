#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	char buf[1024];
	int fd;
	int rdRtr;
		
	for(int i = 1; i < argc; i++){
		
		fd = open(argv[i], O_RDONLY);
	
		if(fd < 0){
			write(STDOUT_FILENO, "wcat: cannot open file\n", 23);
			exit(1);
		}
	
		memset(buf, 0, 1024);
		
		while((rdRtr = read(fd, buf, 1024)) > 0){
			write(STDOUT_FILENO, buf, rdRtr);
		}
	
		close(fd);
		
	}
		
	return 0;
}