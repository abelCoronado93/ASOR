#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>	/* Definition of AT_* constants */
       
#define MAX_BUF 256

int main(){
	
	int fd1 = open("./tuberia", O_RDONLY);
	int fd2 = open("./tuberia2", O_RDONLY);
	int result;
	char buf[MAX_BUF];

	fd_set readset;
	
	do {
		FD_ZERO(&readset); //Inicializamos readset como conjunto vacío
		FD_SET(fd1, &readset);	//Añadimos fd1 a set
		FD_SET(fd2, &readset);	//Añadimos fd2 a set
		result = select(fd2+1, &readset, NULL, NULL, NULL); //Comprobamos si se ha producido cambio en alguno
	} while (result == -1 && errno == EINTR);
	
	//Si se ha producido cambio, lo tratamos
	if(FD_ISSET(fd1, &readset)){
		read(fd1, buf, MAX_BUF);
		printf("%s\n", "Tubería 1:");
	} 
	
	else {
		read(fd2, buf, MAX_BUF);
		printf("%s\n", "Tubería 2:");
	}
	 
	printf("%s\n", buf);

	close(fd1);
	close(fd2);

return 0;
}
