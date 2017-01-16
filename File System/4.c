#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int stat(const char *path, struct stat *buf);

int main(int argc, char **argv){

	int rc;
	struct stat buf;
	rc = stat(argv[1], &buf);

	if(rc == -1){
		perror("Error stat()");
		return -1;
	}
	printf("Major y minor: %i\n", buf.st_dev);
	printf("Número i-nodo: %i\n", buf.st_ino);

	if(S_ISDIR(buf.st_mode)){
		printf("Es directorio\n");
	} else if (S_ISLNK(buf.st_mode)){
		printf("Es simbólico\n");
	} else if (S_ISREG(buf.st_mode)){
		printf("Es regular\n");
	}

	printf("Último acceso: %i\n", buf.st_atime);

	return 1;
}
