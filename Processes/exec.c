#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv){

	pid_t pid = fork();

	switch(pid){

		case 0:
			if(setsid() == -1)
				perror("Error setsid()");
			
			execvp(argv[1], argv+1);
			
		break;

	}

	waitpid(pid); //Queremos que printeé después de ejecutar el comando
	printf("%s\n", "El comando terminó de ejecutarse");

	return 0;
}
