#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>	/* Definition of AT_* constants */
       

int main(int argc, char **argv){

	int rc = mkfifo("./tuberia2", 0777);

	if(rc == -1){
		perror("Error mkfifo()");
		//return -1;
	}
	
	int fd = open("./tuberia2", O_WRONLY);
	
	int size = write(fd, argv[1], strlen(argv[1]));

	close(fd);

return 0;
}

