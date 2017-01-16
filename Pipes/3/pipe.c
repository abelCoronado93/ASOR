#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define PIPE_W 1
#define PIPE_R 0

int main(int argc, char ** argv){
	
	int fds[2];
	pipe(fds);

	pid_t pid = fork();

	switch(pid){

		case -1: 
			perror("Error fork()");
			break;

		case 0: //HIJO
			dup2(fds[PIPE_R], 0); //La lectura estandar (0), se redirecciona a la lectura del pipe
			close(fds[PIPE_W]);
			close(fds[PIPE_R]);
			
			execlp(argv[3], argv[3], argv[4], NULL);

		default: //PADRE
			dup2(fds[PIPE_W], 1); //La escritura estandar (1), se redirecciona a la escritura del pipe fds[PIPE_W]
			close(fds[PIPE_W]);
			close(fds[PIPE_R]);

			execlp(argv[1], argv[1], argv[2], NULL);
	}

return 0;
}
