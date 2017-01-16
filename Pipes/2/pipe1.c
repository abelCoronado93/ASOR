#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>	/* Definition of AT_* constants */
       

int main(int argc, char **argv){

	int rc = mkfifo("./tuberia", 0777);

	int fd = open("./tuberia", O_WRONLY);
	char buf[256];
	scanf("%s", buf);
	int size = write(fd, buf, 256);

	close(fd);

return 0;
}

