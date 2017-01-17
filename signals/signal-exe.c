#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void manejador (int s){
	printf("%s\n", "Ejecutando tarea programada..");
}

int main(int argc, char ** argv){

	int segs = atoi(argv[1]);

	pid_t pid = fork();

	if(pid == 0){
		alarm(segs);
		struct sigaction sa;
		
		sa.sa_handler = &manejador;

		sigaction(SIGALRM, &sa, NULL);

		pause();
		//mkdir("tmp", 0777);
		int fd = creat("examen.out", 0666);
		chmod("examen.out", 0666);

		dup2(fd, 1);

		execlp(argv[2], argv[2], argv[3], NULL);
		return 0;

	} else {
		printf("Ejecución programada en %i segundos por proceso %i\n", segs, pid); 
		wait(NULL);

	}

	return 0;
}