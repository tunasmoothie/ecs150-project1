#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	if(argc < 2){
		write(STDOUT_FILENO, "wgrep: searchterm [file ...]\n", 29);
		exit(1);
	}
	
	int fd;
	fd = (argc == 2) ? STDIN_FILENO : open(argv[2], O_RDONLY);
	if(fd < 0){
		write(STDOUT_FILENO, "wgrep: cannot open file\n", 24);
		exit(1);
	}
	
	char buf;
	std::string line;
	
	while(read(fd, &buf, 1) > 0){
		
		line += buf;
		
		if(buf == '\n'){
			if(line.find(argv[1], 0) != std::string::npos)
				write(STDOUT_FILENO, line.c_str(), line.size());
				
			line = "";
		}
	}
	if(line.find(argv[1], 0) != std::string::npos)
		write(STDOUT_FILENO, line.c_str(), line.size());
	
	close(fd);
	exit(0);
}